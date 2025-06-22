-练习如何回答 System Design 题目

-面试时可以按照 4-6-2 原则 进行回答：
- 4 分钟：需求分析
    Clarify 需求，确认是否有 SLA、QPS 需求
    识别核心功能和非功能性要求
- 6 分钟：架构设计
    画出整体架构 (客户端 → 负载均衡 → 服务层 → 数据层)
    解释各个组件的作用
    讨论可扩展性、容错性
- 2 分钟：优化 & 取舍
    讨论 Trade-offs (数据一致性 vs 可用性)
    方案对比 (SQL vs NoSQL, Monolithic vs Microservices)
- 一年 是 30  million 秒
- 一天 是 100 k 秒

- Template
  - Requirements
    - Functional requirements
    - Non-Functional requirements
  - Entities
  - APIs 
  - [High-Level Design](./high_level_design.png)
  - Deep Dive

- 4. RATE LIMITER
  counting / sliding window / redis hash {userID: (count, startTime)} for 1 hour / consistent hashing / different rate limiters for different APIs
  - purpose
    - DDOS
    - lower the cost
    - VIP for higher rate
    - spike traffic elimination
  - Requirements
    - Functional requirements 
      - 15 requests/second user
      - conpatible with cluster settings
    - Non-Functional requirements 
      - high availability (protect from attack)
      - low latency (introduce low or no latency)
  - Entities
    - User
    - sliding window
  - APIs
    - GET  resources/ -> 429 too many requests
    - POST resources/ -> 429
  - [Design](./4.high_level_design.png)
    - Throttling (http 429 too many requests)
      - hard
      - soft
      - dynamic
    - algo1: counting {userID: (count, startTime)}
      CurrentTime – StartTime >= 1 min
      - Atomicity: read-and-then-write” behavior can create a race condition
        - two requests at the same time can get the same count
        - redis servers with lock in a distributed setup
      - alow twice the limit
      - Mem usage
        userID 8 bytes
        counter 2 bytes
        startTime 2 bytes only store minute and second
        1 million users
        hash table overhead 20 bytes/record
        lock overhead 4 bytes number lock
        1 million * (8+2+2+20+4)bytes = 36 MB
        
    - algo2: sliding window
      - redis sorted set {userID: SortedSet<Time>}
        8 (userID) + (4 (time) + 20 (sorted set overhead)) * 500 request/hour + 20 (hash-table overhead) = 12KB
        * 1 million = 12GB
      - expensive
    - algo3: 1+2
      1 min counter (count, startTime) using Redis Hash and set expire in 1 hour
      at most 60 counters/hour
      8 + (4 + 2 + 20 (Redis hash overhead)) * 60 + 20 (hash-table overhead) = 1.6KB
      * 1 million = 1.6GB
  - Data Sharding and Caching
    - consistent hashing by userID
    URL Shortener; we can have different rate limiter for createURL() and deleteURL() APIs for each user or IP.
    - cache write back later
  - limit by ID or IP
    - IP bad user can limit other good users in the same network
      IPv6 huge number from even one computer
    - ID
      - Login Auth bad user can enter bad password for the good user DoS
    - IP + ID
      - more memory and storage  

- 6. KEY-VALUE STORE : Dynamo
  Partition | Replication | Consistency(Conflicts) | Scailability | Cluster state
  - CAP 中的 A (Available) P (Partition Tolerance)
  - APIs
    - get(key) -> object && context
    - put(key, context, object)
      The context is always stored along with the object and is used like a cookie to verify the validity of the object supplied in the put request.
  - Data partition
    - [[consistent hashing]] with virtual nodes
      randomly distributed and non-contiguous
      - evenly distributed && rebalancing fast
      - heterogeneous machines
        lower ranges for less powerful machines
      - no hot spots
  - Replication
    - replication factor 
    - hinted handoff
      服务器挂了之后，replication 顺延 with hint
    - Sloppy quorum
      是一个容错写入机制。
      指的是当一部分节点不可用时，写入操作可以被暂时存储在“临时”节点上，稍后再同步回正确节点。
      目的是提高系统的可用性
    - [conflict scenario](./6.Conflict_scenario.png)
  - Vector clock and conflicting data
    - server A and server B
      {A:1} {A:2} {B:1} we only know {A:1} is older
      {A:2} and {B:1} need to be resolved by client
      或者 merge {A:2} 和 {B:1} 的 object
    - Conflict-free replicated data types
    - Last-write-wins
  - data reconciliation
    - Merkle trees, solve the conflict in the background
  - Cluster states
    - gossip protocol and [seed nodes] (know all other nodes)
  - follow up: 如何处理 TTL（Time-To-Live）的删除
    - Lazy Delete + Cron Job
  


- 7. UNIQUE ID GENERATOR IN DISTRIBUTED SYSTEMS
  - 需求分析: 
    - unique
    - 64bit
    - 10000 IDs/second
    - increasing by time
  - databases auto_increment
    - multiple data centers 网络延迟 数据不一致
    - time 可能不是来自同一个服务器，不一定是递增的
    - 添加服务器减少服务器都难办
  - Twitter snowflake approach
      |  41 bits  |    5 bits     |   5 bits   |     12 bits     |
      |-----------|---------------|------------|-----------------|
      | Timestamp | Datacenter ID | Machine ID | Sequence number |
      | Millisecs |  32 centers   | 32 machine |reset millisecond|








- 8. URL SHORTENER
  - 需求分析: 
    100 million/day
    write/second = 1160
    read         = 11600
    10 years records     = 100 million/day * 365 * 10 years = 365 billion
    storage for 10 years =  365 billion * 100 bytes = 36.5 TB
    values in short URLs: 0 a A = 62 chars
    length of short URLs: 7 
    - Functional Requirements（功能性需求）
      1. URL 缩短:   用户提供一个 long URL，系统返回一个唯一的 short URL。
      2. URL 重定向: 输入短链接，系统能够正确查找到对应的长链接并重定向。
      3. 唯一性保证:  对于每一个 long URL（或用户请求），生成的 short URL 是唯一的，避免冲突。
    - Non-Functional Requirements
      - Scalability ｜ High Availability ｜ Low Latency
  - Entities
    URL mapping
    User
  - APIs
    - POST /shorten/{longURL=?} -> shortURL
    - GET  /{shortURL}          -> longURL
  - [URL Shortening POST](./8.URL%20Shortening.png)
    - Database format:
      |    ID   | Short URL | Long URL 
      |---------|-----------|----------
      | 12345   |  zn9edcu  | https://en.wikipedia.org/wiki/Systems_design
      | 56644   |  fg8723j  | https://en.wikipedia.org/wiki/Systems
    - hash
      - collision
        - Bloom Filter: if element is a member of the set
    - BASE 62 on unique ID (not on the long URL)
      - not fixed len
      - ID generator [Chapter 7: Design A Unique ID Generator in Distributed
Systems]
      - unique
  - [URL Redirecting (GET)](./8.URL%20Redirecting.png)
  - follow up 
    - Analytics
    - Database scaling
    - Rate limiter (Chapter 4: Design a rate limiter)

- 9. WEB CRAWLER
  - Requirements
    - Functional
      - Crawl the full web starting from seed urls
      - Extract text data and store
    - Non-functional
      - Fault tolerance 
      - Politeness
      - Scale to 10B pages
      - Efficient to crawl in 5 days
  - API or System Interface
    - Input: Seed URLs to start crawling from.
    - Output: Text data extracted from web pages.
  - Data Flow
    1. Take seed URL from frontier and request IP from DNS
    2. Fetch HTML from external server using IP
    3. Extract text data from the HTML.
    4. Store the text data in a database.
    5. Extract any linked URLs from the web pages and add them to the list of URLs to crawl.
    6. Repeat steps 1-5 until all URLs have been crawled.
  - [High Level Design](./9.high_level_design.png)
  - identify bottleneck 
    - wait for web response
    - saparate crawl and parse
  - [improvement](./9.improvement.png)
    - crawl (distributed DNS/crawling) (DNS cache)
    - parse (on-demand)
  - failed URL retry / backoff 1,2,4,8 seconds
  - [[MATH]] how many crawlers do we need?
    - 10B pages / 5 days = 2000 pages/second
    - 1 crawler can crawl 100 pages/second
    - 20 crawlers
  - 去重
    - URL 去重
      - hash table
    - 内容去重
      - checksum
    - bloom filter

- 10. NOTIFICATION SYSTEM
  - Requirements
    - Functional
      - 多渠道通知支持：
        系统应支持通过多种渠道发送通知，如 Email、SMS、Push Notification、In-App 等。
      - 通知投递状态追踪：
        系统应能记录通知是否成功发送、失败原因，以及用户是否阅读（可选，取决于渠道）。
    - Non-functional
      - 高可用性（High Availability）：
        通知系统应设计成高可用架构，确保不会因为部分服务宕机导致整个通知链中断
      - 可扩展性（Scalability）：
        系统需要支持水平扩展，能在高峰期处理数百万条通知请求（比如黑五、双十一活动时）。
      - 低延迟（Low Latency）：
        系统应能保证通知在事件发生后尽快（例如 <1 秒内）送达用户，尤其是对 Push/In-App 通知。
  - Entities
    User: user_id, device_id, phone, email
    Notification: notification_id, user_id, type, content
  - APIs
    - POST /notifications/send
      - body: {user_id, type, content}
      - response: {status, notification_id}
    - GET /notifications/status/{notification_id} -> {status, error_message}
  - [High Level Design](./10.high_level_design.png)
    - Cache: User info, device info, notification templates are cached.
    - DB: It stores data about user, notification, settings, etc.
  - [Rate limiting / Retry mechanism / Events tracking (clicks, opens)](./10.improved_design.png)

- 1-11. NEWS FEED SYSTEM
  - Requirements
    - Functions
      - Create Posts
      - Follow people
      - View feed
    - Non-Functional Reuquirements
      - Posts visible in < 2 minutes (eventually consistent)
      - Posting and viewing posts < 500ms
      - Massive number of users 2B
      - Unlimited followers/follows
  - Entities
    User
    Post
    Follow
    // added afterward feed: {uid : [post_id1, post_id2, ...]}
  - APIs
    - POST /post/create -> post_id
    - POST /user/{user_id}/follow -> success
    - GET  /feed
  - cache (500 posts) for each first time user
    - get only 50 feeds when they scroll down
  - [High Level Design](./11.Simple_Solution.png)
    - Create Post
    - follow people
    - get feed of posts from the people they follow
      1. get all the followees from graph DB
      2. get posts from each followee
      3. add feed to the cache
  - Problem
    - 1 user can follow many people
    - these people can have a lot of posts
    - set of posts might be huge
  - [Improved Design](./11.Improved_Solution.png)
    - update the feed table when a new post is created
      1. get all the followers from graph DB
      2. add all the followers to a kafka queue 
      3. worker can consume the queue and update the feed table
  - problem
    - inactive users' feed is also geting updated
    we can combine the two approaches tier1: cache | tier2: DB | tier3: real-time computation 


- 1-12. CHAT SYSTEM
  - 1. Requirements
    - Functional
      - 消息发送与接收：
        用户可以通过 Chat Servers 发送和接收实时消息，系统应确保消息能快速送达目标用户
      - 用户在线状态管理：
        Presence Servers 负责追踪用户的在线/离线状态，使聊天系统能够显示用户是否在线。
      - 消息通知：
        当用户离线/上线时，Notification Servers 应通过通知（如推送通知）告知用户有新消息。
    - Non-Functional
      - 高可用性（High Availability）：
        所有关键组件（API servers、Chat servers、KV stores 等）都应具备冗余部署，避免单点故障。
      - 低延迟（Low Latency）：
        消息应以毫秒级延迟完成传输，特别是 WebSocket 通道下的实时通信。
      - 可扩展性（Scalability）：
        架构应支持横向扩展，能够应对数百万用户并发连接和大量消息流量（通过分布式 KV store 和可扩展服务器池实现）。
  - 2. Entities
    - User
    - Message (1-1)
        | message      |
        |--------------|
        | message_id   |
        | message_from |
        | message_to   | 
        | content      |
        | timestamp    |

    - Message (Group)
        | message      |
        |--------------|
        | channel_id   |
        | message_id   |
        | user_id      |
        | content      |
        | timestamp    |
      - message_id
        - Chapter 7: Design a unique ID generator in a distributed system
          - unique
          - chronological
            |  41 bits  |    5 bits     |   5 bits   |     12 bits     |
            |-----------|---------------|------------|-----------------|
            | Timestamp | Datacenter ID | Machine ID | Sequence number |
            | Millisecs |  32 centers   | 32 machine |reset millisecond|
        - id is only unique within a group
  - 3. APIs
    - POST /message/send -> message_id
    - GET  /message/{user_id} -> message_list
    - GET  /message/{group_id} -> message_list
    - Group chat vs 1-on-1 chat
    - send / receive message
      sender ---alive http--> chat service ---???method???--> receiver 
      - polling: continuously check for new messages
      - long polling: receiver sends request and server holds it until new message arrives
        - may not connect to the same server
        - don't know if the receiver is disconnected 
        - inefficient, still make connections
      - WebSocket: bi-directional and persistent
        - sender <--WebSocket--> chat service <--WebSocket--> receiver
  - [High Level Design](./12.chat%20system.png)
    - Presence servers: manage online/offline status 
    - API servers: handle everything including user login, signup, change profile, etc.
    - Notification servers: send push notifications.
    - KV store: chat history
  - storage 
    - Chat history: KV store
    - user profile, friends list: DB, graph DB
  - Dive Deep
    - Service discovery
      - [zookeeper](./12.zookeeper.png)
        recommends the best server bassed on location, capacity .etc.
  - [message flow](./12.message_flow.png)
    3. Chat server 1 sends the message to the message sync queue.
    4. The message is stored in a key-value store.
    5.b. If User B is offline, a push notification is sent from Push Notification (PN) servers.
  - [Message synchronization across multiple devices](./12.sync_flow.png)
    - make use of current message_id
  - [Online presence](./12.Online-off-line.png)
    - login/logout = online/offline
    - heartbeat
  - online statue fanout
    - publish-subscribe model
     

- 13. AUTOCOMPLETE SYSTEM
  data gathering ｜ query service ｜
  - other names: typeahead / design top k
  - 需求分析: 
    - QPS
    - latency 100ms
    - top 5 most frequent
  - Data gathering service (real-time)
    | Query   | Frequency |
    |---------|-----------|
    | twich   | 100       |
    | twitter | 500       |

    SELECT * FROM tab
    WHERE query LIKE 'prefix%'
    ORDER BY frequency DESC
    LIMIT 5
    - 缺点 
      QPS 太多，slow
      top k 不咋变
  - Data gathering service (late update, weekly)
    - log -> aggregated data -> Trie DB -> Trie cache
    - log format: 
      | Query    |    Time      |
      |----------|--------------|
      | Linkedin | 250201 13:00 |
    - aggregation
      | Query    |    Time      | Frequency |
      |----------|--------------|-----------|
      | Linkedin | 250201       | 120000    |
    - Trie DB
      - trie O(p) + O(c) + O(clogc) <-- slow 
          (limit)  (cache top query in each node)
      - [trie + cache O(1)](./13.trie%20with%20cache.png)
      - Document store: serialize + MongoDB
      - Key-value store: each node is key
    - Trie cache
      - snapshot of DB
  - [Query Service](./13.Query%20Service.png)
    - AJAX area update (not refresh the whole web page)
    - Browser caching (Google)
    - [Trie delete hateful suggestion](./13.Delete.png)
      also do it when build trie
  -  [Scale the storage (trie cannot fit in one server)](./13.Sharding.png)
    - sharding by first char or first two char ... 
  - follow up
    - multiple languages
      Unicode
    - top search queries different in countries
      different tries and CDNs
    - trending (real-time) search queries


- 4. Distributed Message Queue: kafka
  collecte big data and real-time analysis
  - queue model
    - 1-to-1
  - publish-subscribe model
    - 1-to-many
  - Deep Dive
    - a topic can be partitioned into multiple brokers
      topic1
      | broker 1    | broker 2    | broker 3    | 
      | partition 1 | partition 2 | partition 3 |
    - how to find a message? 
      - topic + partition + offset 
      - topic + key       + offset
    - dumb broker / smart consumer
    - replica (leader + follower)
      - in-sync replica can become leader (min ISRs = 3)
        - high-water mark (at least 3 replicas have the same message )
          - expose to consumer 
  - Consumer Groups (act like a single consumer for a topic)
    - each consumer in a group can read from one partition
    - consumer# = partition#
  - Split brain
    - Generation clock
  - producer asyc/leader/leader+Quorum
  - consumer at-most-once/at-least-once/exactly-once




- 5. Metrics Monitoring and Alerting System
  write heavily: 10 million operational metrics are written
  read spikingly
  - Data collection
  - Data transmission
  - Data storage
    - time series database
      - InfluxDB / Prometheus
  - Alerting
  - Visualization
  - [High-level design](./5.high_level_design.png)
  - Metrics Source --> Metrics Collectors auto-scaling
    - |              |    pull      |   push     |
      |--------------|--------------|------------|
      | debug        | /metrics     |            |
      | Health check | /metrics     | 可能网络问题 |
      | Short jobs   |              | pull 间隔长 |
      | Firewall     | 可能不能访问   | LB + group |
      | Performance  | TCP          | UDP        |
      | Firewall     | 可能不能访问   | LB + group |
      | authenticity | guaranteed   |            |
  - Metrics Collectors --> Time series DB (what if DB is down)
    metrics transmission pipeline
    Metrics Collectors --> kafka --> consumer --> Time series DB
  - Time series DB <-- Query Servers (+ Cache)
  - [alert_system](./5.alert_system.png)

- 2-6. Ad Click Event Aggregation (top-k)
  - requirements
    - functional
      - Aggregate the number of clicks of ad_id in the last M minutes.
      - Return the top 100 most clicked ad_id every minute.
      - Support aggregation filtering by different attributes.
    - non-functional
      - Facebook or Google volume
      - aggregation result is accurate
      - handle delayed or duplicate events
      - Latency should be a few minutes
  - Entities
    - clicks | most 100 clicked
  - APIs
    - GET aggregated_count/{:ad_id} -> count (in the last M min)
    - GET top_100/                  -> LIST: [ad_ids] (in the last M min)
    - raw data (first message queue)
      | ad_id |     timestamp      | user_id | location |
      |-------|--------------------|---------|----------|
      | 12345 | 2025-04-01 00:00:01| 1       | CA       |
      | 12345 | 2025-04-01 00:00:03| 2       | WA       |
      | 22222 | 2025-04-01 00:00:01| 3       | CA       |
    - aggregated data (second message queue)
      | ad_id |     timestamp      | count |
      |-------|--------------------|-------|
      | 12345 | 2025-04-01 00:00   | 2     |
      | 22222 | 2025-04-01 00:00   | 1     |
    - top 100 (second message queue)
      | update_time_minute | most_clicked_ads |
      |--------------------|------------------|
  - [high-level design](./2-6.top_k_every_min.png)
    streaming: near real-time
    - [Aggregation service](./2-6.Aggregation_service.png)
  - Dive Deep
    - [Streaming vs batching](./2-6.replay.png)
    - Delayed events: read from kafka for 5 more seconds
    - Aggregation window
      - 1 minute  fixed window
      - M minutes sliding window 
    - Data deduplication
      - [aggragation service outage](./2-6.duplicated_events.png)
        - [distributed transaction](./2-6.Distributed_trans.png)
    - scalability
      - kafka
        - partitioning (pre-allocate enough partitions)
          - Hashing ad_id as key to make sure the same ad_id is sent to the same partition
        - Add Brokers / Consumers & Rebalance
        - Hashing key (ad_id) find in the same partition
      - [Aggregation service](./2-6.scale_aggregation_service.png)
        - Flink intead of map-reduce
          - stream aggregation
          - aggregation window  1 min
          - flush intervals    10 seconds
      - database
        - sharding by ad_id
        - consistent hashing
    - hotpot for popular ad_id
      - [auto scaling the aggregation node](./2-6.auto_scale_aggregation_node.png)
      - before go to kafka add [0-N + ad_id] to the shard_id (or key in the kafka topic)
    - Fault tolerance
      - snapshot recovery from the last time they read from kafka (S3)
      - no worries about the kafka (it is already fault-tolerant and highly available) 
    - data reconciliation using the batch processing
    


- 2-10. Real-time Gaming Leaderboard
  - [high level design](./2-10.high_level_design.png)
  - workflow                        -> Analytic Service
    - user -> game service -> kafka -> Leaderboard Service(win ? +1 : -1)
                                    -> Push Notification Service
  - ❌ Database slow
  - ✅ [redis sorted set](./2-10.Redis_skipped_list.jpg)
    - O(log n)

  -                       -> Leaderboard sorted set 
  - user -> load balancer -> User profile + User points
                          -> Top 10 user cache
  - redis sharding
    [top 1-100] - [top 101-200] - [...] ...



- LinkedIn Job Recommendation System (1-11. NEWS FEED SYSTEM)
  show recommendation after user open app
  should display at least 5 jobs per reasons, reason could be anything from
  your profile (location, education, industry, etc.)
  - Functional requirements
    - reason
      - Location
      - post by followee
      - skill set
      - frequent item set
      - popularity

  - Non-functional requirements
  - Capacity Estimation
  - Workflow
    - user A add post
    - user B,C 
      - getUserFeed()
      - pushFeedToUser() (Long Poll)
  - cache + DB1
    - User 表
    - Entity 表
    - UserFollow 表
  - cache + DB2
    - FeedItem 表
  - feed cache
    - 1 post by followee
      - {user A: post1, post2, ... 5 at most}
      - user B get all the followers, including user A (graph DB)
      - aggregate all followers' posts
    - 2 location
      - {CA: pos1, pos2..., WA: pos1, pos2...}
    - skill set
      - product of user skill set and job skill set
    - frequent item set / collaborative filtering
      other users applied for this job also applied A, B, C
    - popularity
      - accumulator for each job [10. Real-time Gaming Leaderboard]

- IP 黑名单服务
  - 要设计一个 malicious IP blacklist service，并且假设已经提供了一个 isMalicious(ip) API 来判断某个 IP 是否恶意，我们可以从以下几个方面进行系统设计：
  - Requirements
    - 功能性需求（Functional Requirements）
        •	接收 IP 并判断是否恶意。
    - 非功能性需求（Non-Functional Requirements）
        •	高并发、高可用（面向互联网开放）。
        •	快速响应时间（毫秒级别查询）。
        •	高可扩展性（海量 IP，分布式部署）。
        •	数据一致性与持久性（黑名单不能轻易丢失）。
  - API
  - 🧱 2. 高层设计组件（High-Level Design）
    +-----------------+       +-----------------+       +----------------------+
    |  Client Request |  -->  |  API Gateway    |  -->  |  IP Blacklist Service|
    +-----------------+       +-----------------+       +----------------------+
                                                                |
                                                                v
                          +---------------------------------------------+
                          |     Cache Layer (e.g., Redis / Memcached)   |
                          +---------------------------------------------+
                                                                |
                                                                v
                          +---------------------------------------------+
                          |    Persistent DB (e.g., Cassandra, DynamoDB)|
                          +---------------------------------------------+
                                                                |
                                                                v
                                                    +--------------------+
                                                    | isMalicious(ip) API|
                                                    +--------------------+
  - 🧠 3. 核心流程逻辑
    - 查询 IP 是否恶意（GET /isBlacklisted?ip=1.2.3.4）
      1. 查询缓存（Redis）是否存在该 IP 的状态：
        •	命中：直接返回结果。
        •	未命中：
        •	调用 isMalicious(ip)。
        •	若返回 true，则加入缓存和持久层黑名单表中。
        •	返回查询结果。
      2. 后台批量检查任务 corn job
        •	定期从数据库中抽样非黑名单 IP，重新验证是否变成 malicious。
        •	支持过期清理机制（例如某些 IP 一段时间后不再被判定恶意）。
  - 🗃️ 数据存储设计
    - Redis 缓存结构
        Key: "blacklist:1.2.3.4"
        Value: true / false
        TTL: 24 hours or configurable
    - 持久层（NoSQL 或关系型）
        IP Address	IsMalicious	FirstDetected	LastChecked	Source
        1.2.3.4	    true      	2025-04-01	  2025-04-04	isMalicious API
  - 🔒 安全性设计
      •	限制每秒查询次数（rate limiting）。
      •	防止恶意用户批量测试（加认证/风控）。
      •	日志记录所有 API 调用及判定结果。
    ⏱️ 可选优化
      •	异步批量验证：将未知 IP 扔入消息队列中，由 worker 异步调用 isMalicious(ip)。
      •	分布式缓存：使用 Redis Cluster 实现横向扩展。
      •	灰度更新机制：对某些 IP 检查结果模糊的情况使用投票机制、机器学习判断等。
      


- 3-3. Ticket Master
  - Functional Requirements
    - 查看剩余票数
    - 购买票 可一次多张 GA (General Admission)
  - Non-Functional Requirements
    - High Availability
    - Consistency
  - Entities
    - Event
        event_id
        total_tickets
        remaining_tickets
    - order
        order_id
        event_id
        ticket_count
        user_id
  - APIs
    - GET /events/{event_id} -> remaining_tickets
    - POST /purchase?event_id=123&ticket_count=2 —> order_id
  - [High-Level Design](./3-3.High_level.png)
  - Problem: 
    reserve tickets for 10 min when user clicks purchase
    - distributed lock 
      - Redis Lua 在单节点内存中做原子扣减 with TTL
      一旦 Redis 预占成功 + 付款成功
      1.	生成订单消息，包含 userId, eventId, wantCount, requestId
      2.	投递到消息队列（Kafka / RabbitMQ / SQS）
    - OCC (Optimistic Concurrency Control)
      一次购票需要在存储层同时完成两件事：
        1.	扣减库存：ticket.inventory = ticket.inventory - N，且要求执行后 inventory ≥ 0。
        2.	写入订单：在 order 表插入一行 { user_id, ticket_id, count=N }。
        关键在于：两步必须要么都成功、要么都不生效，即原子性。
      while (true) 
        UPDATE Event SET remaining_tickets = ?, version = [[old_version+1]]
         WHERE event_id = ? AND version = [[old_version]]
        rollback or update Order
    - 付款不成功 
      Keyspace Notification 监听过期事件
      Lua 释放脚本
    - spike elimination
      kafka 
  - [Improvement](./3-3.improvement.png)






- 3-4. Live Commenting System
  - Functional Requirements
    - post comment
    - view new comments
    - view history comments 
  - Non-Functional Requirements
    - support millions of concurrent videos &&
      thousands of comments per second per live video.
    - availability >> consistency
    - low latency near-real time < 200ms
  - Entities
    - comment
    - video 
    - user
  - APIs
    - POST /comments/:liveVideoId
    - GET  /comments/:liveVideoId ? cursor={last_comment_id}
    - get comments
      comment service ---???method???--> receiver 
      - polling: continuously check for new messages
      - long polling: receiver sends request and server holds it until new message arrives
        - may not connect to the same server
        - don't know if the receiver is disconnected 
        - inefficient, still make connections
      - WebSocket: bi-directional and persistent
        - comment service <--WebSocket--> receiver
        - non-http protocol
        - all infra needs to support WebSocket  [client] <-> [API gateway AWS] <-> [comment service]
      - ✅ SSE (Server-Sent Events) (200ms)
        - unidirectional
        - HTTP 
        - built-in reconnection by browser
        - light weight
  - [High-level Design](./3-4.Live_Comment.png)
    - POST 写入 → Comment Service → Kafka
	  - Kafka partition (基于 videoId 的 rendezvous hash) → 对应 fan-out 实例
	  - SSE 订阅（同样用 videoId 的 rendezvous hash）→ 路由到同一实例
	  - fan-out 实例 只消费自己那份 partition，并维护那批 SSE 连接 → 推送新评论
      - 保证 SSE 路由层和 Kafka Producer（/Consumer）看到的「活跃节点列表」一致，并用同一个 Rendezvous Hash 实现映射。
        - zookeeper 
        - kafka admin



- 3-5 YouTube Top K Videos
  - Requirements
    - Functional requirements
      - Query TopK videos (max 1000)
      - 1 hour, 1 day, 1 month, all-time
    - Non-Functional requirements
      - < 1 min delay between when a 观看 occurs and when it should be tabulated
      - No approximations
      - get result fast < 100ms
  - Entities
    video
    view
    window -> Minute/Hour/Day/All-time
  - APIs 
    - input [video_id, timestamp]
    - GET /views/top?window={WINDOW}&k={K}
  - [High-Level Design](./3-5.high_level_design.png)
  - Deep Dive
    - How to calculate hour count / day count?
      - [two pointers](./3-5.two_pointers.png)
        when decrementing / incrementing the count, heap should be shiftDown / bubbleUp
    - client get top k
      - cache with TTL 40s (allow < 1 min delay)
    - 状态持久化与恢复
      每个 Counter 实例本地状态（counts + heap）定期 snapshot 到持久化存储（Blob、RocksDB changelog）；
      重启或新增实例可以快速从最近一次 snapshot + Kafka replay 恢复计数，不丢数据。
    - hot spot
      对于播放量超级高的“爆款”视频，可在哈希后再做二级分片（给同一个 videoId 多个 shard key），多路写入后聚合它们的子计数；
      这样避免单个 Counter 成为瓶颈。
    - Min Sketch
      Bloom Filter 只是告诉你“有没有见过 X？”
      Min Sketch   告诉你“大概见过多少次 X？”

- 3-6 LeetCode
  - Functional Requirements
    - view a list of coding problems.
    - view a given problem, code a solution
    - submit  solution and get instant feedback.
    - view a live leaderboard for competitions.
  - Non-Functional Requirements
    - availability > consistency.
    - support isolation and security when running user code.
    - eturn submission results within 5 seconds.
    - scale to support competitions with 100,000 users.
  - Entities 
    - Problem
    - Submission
    - Leaderboard
  - APIs
    - GET /problems?page=1&limit=100 -> Partial<Problem>[]
    - GET /problems/:id?language={language} -> Problem
    - POST /problems/:id/submit -> Submission
    - GET /leaderboard/:competitionId?page=1&limit=100 -> Leaderboard
  - [High-Level Design](./3-6.high_level_design.png)
    - DB 前面可以加个 cache
  - Deep Dive
    - how to run test cases?
      - serialize the test cases
      - 各语言 deserialize && compare 
    - how to support 100,000 users? 
      - Horizontal auto-scaling w/ Queue
        async but polling (GET /check/:id)


- 3-7 Netflix / YouTube
  - Requirements
    - Functional requirements
      1. Users can upload videos.
      2. Users can watch (stream) videos.
    - Non-Functional requirements
      1. availability > consistency
      2. uploading and streaming large videos (10s of GBs).
      3. low latency streaming of videos, even in low bandwidth environments
      4. ~1M videos uploaded per day, 100M videos watched per day
      5. support resumable uploads.
  - Entities
    - video 
    - video metadata
  - APIs 
    - POST /videos   (only for small videos)
    - GET  /videos/:id -> video && metadata 
  - [High-Level Design](./high_level_design.png)
    - [Video Upload](./3-7.video_upload.png)
      1. cut into small segments
      2. get presigned URL from S3
      [client] <-> [API Gateway] <-> [video service] <-> [S3] <-> [video processing service]
                                                     <-> [video metadata DB]  <-|
      3. upload directly to S3
    - [Video Streaming](./3-7.video_streaming.png)
      1. download manifest file (有哪些码率/清晰度可选，分片的 URL、时长、顺序)
      2. download the first segment from S3 / CDN
  - Deep Dive
    - hot videos 
      - cache in front of [video metadata DB]
    - resumable uploads
      MD5 + BitMap
    - scaling 
      - Video Service stateless horizontal scaling
      - Video Metadata - Cassandra 
        - consistent hashing + shard by video_id 
        - cache in front of DB 
      - Video Processing Service
        - kafka + more workers
      - S3 
        - shard by video_id
        - CDN (both segments and manifest files)
          当用户请求视频 12345 的 Manifest 时，视频服务计算 shard = hash(12345)%10 = 7
          Manifest 里所有分片 URL 都以 https://videos-7.cdn.example.com/12345/... 开头
          客户端对 videos-7.cdn.example.com 发起 DNS 请求，CDN DNS 根据用户地理+负载，返回最优 PoP 的 IP。
        
- 3-8. Yelp / nearby location
  - Geo-hash / quad-tree