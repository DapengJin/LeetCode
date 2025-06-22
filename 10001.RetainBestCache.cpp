#include <unordered_map>
#include <queue>
#include <utility>

// public class RetainBestCache<K, T extends Rankable> {
//     int entriesToRetain;
//     HashMap<K, T> map = new HashMap<K,T>();
//     DataSource<K,T> ds;

//     /* Constructor with a data source (assumed to be slow) and a cache size */
//     public RetainBestCache(DataSource<K,T> ds, int entriesToRetain) 
//     {
//     //impliment here
//     }

//     /* Gets some data. If possible, retrieves it from cache to be fast. If the data is not cached,
//     * retrieves it from the data source. If the cache is full, attempt to cache the returned data,
//     * evicting the T with lowest rank among the ones that it has available
//     * If there is a tie, the cache may choose any T with lowest rank to evict.
//     */
//     public T get(K key) 
//     {
//     //impliment here
//     }

//     /*
//     * For reference, here are the Rankable and DataSource interfaces.
//     * You do not need to implement them, and should not make assumptions
//     * about their implementations.
//     */
//     public interface Rankable 
//     {
//     /**
//     * Returns the Rank of this object, using some algorithm and potentially
//     * the internal state of the Rankable.
//     */
//     long getRank();
//     }

//     public interface DataSource<K, T extends Rankable> {
//     T get(K key);
//     }
    
template <typename K, typename T>
class RetainBestCache {
public:
/* Constructor with a data source (assumed to be slow) and a cache size */
    RetainBestCache(DataSource<K, T>* ds, int entriesToRetain)
        : dataSource(ds), maxSize(entriesToRetain) {}

    /* Gets some data. If possible, retrieves it from cache to be fast. If the data is not cached,
    * retrieves it from the data source. If the cache is full, attempt to cache the returned data,
    * evicting the T with lowest rank among the ones that it has available
    * If there is a tie, the cache may choose any T with lowest rank to evict.
    * 
    * item = dataSource->get(key)
    * 
    * rank = item.getRank()
    */
    T* get(const K& key) {
        auto it = cache.find(key);
        if (it != cache.end()) {
            return &(it->second);
        }

        T item = dataSource->get(key);
        if (cache.size() >= maxSize) {
            evictLowestRank();
        }

        cache[key] = item;
        rankQueue.emplace(item.getRank(), key);
        return &cache[key];
    }

private:
    struct RankComparator {
        bool operator()(const std::pair<long, K>& a, const std::pair<long, K>& b) {
            return a.first > b.first; // Min-heap based on rank
        }
    };

    void evictLowestRank() {
        while (!rankQueue.empty()) {
            K keyToEvict = rankQueue.top().second;
            rankQueue.pop();
            if (cache.count(keyToEvict)) {
                cache.erase(keyToEvict);
                break;
            }
        }
    }

    std::unordered_map<K, T> cache;
    std::priority_queue<std::pair<long, K>, std::vector<std::pair<long, K>>, RankComparator> rankQueue;
    DataSource<K, T>* dataSource;
    int maxSize;
};