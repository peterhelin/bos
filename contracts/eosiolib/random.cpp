#include "random.hpp"

#include "system.h"
#include "time.hpp"
#include "transaction.h"
#include "types.h"

#include "random.h"


namespace eosio {

    std::unique_ptr<std::seed_seq> seed_timestamp_txid() {
        uint64_t current = current_time();
        uint32_t* current_halves = reinterpret_cast<uint32_t*>(&current);

        transaction_id_type tx_id;
        get_transaction_id(&tx_id);
        uint32_t* tx_id_parts = reinterpret_cast<uint32_t*>(tx_id.hash);

        return std::make_unique<std::seed_seq>(std::initializer_list<uint32_t>{current_halves[0], current_halves[1],
                                                                               tx_id_parts[0], tx_id_parts[1], tx_id_parts[2], tx_id_parts[3],
                                                                               tx_id_parts[4], tx_id_parts[5], tx_id_parts[6], tx_id_parts[7]});
    }

    std::unique_ptr<std::seed_seq> seed_timestamp_txid_signed() {
        char buf[sizeof(signature)];
        size_t size = producer_random_seed(buf, sizeof(buf));
        eosio_assert( size > 0 && size <= sizeof(buf), "buffer is too small" );
        uint32_t* seq = reinterpret_cast<uint32_t*>(buf);

        return std::make_unique<std::seed_seq>(seq, seq + 16); // use the leading 64 bytes, discard the last 2 bytes
    }

    std::minstd_rand0 minstd_rand0(const seed_seq_ptr& seed) {
        return std::minstd_rand0(*seed);
    }
    std::minstd_rand minstd_rand(const seed_seq_ptr& seed) {
        return std::minstd_rand(*seed);
    }
    std::mt19937 mt19937(const seed_seq_ptr& seed) {
        return std::mt19937(*seed);
    }
    std::mt19937_64 mt19937_64(const seed_seq_ptr& seed) {
        return std::mt19937_64(*seed);
    }
    std::ranlux24_base ranlux24_base(const seed_seq_ptr& seed) {
        return std::ranlux24_base(*seed);
    }
    std::ranlux48_base ranlux48_base(const seed_seq_ptr& seed) {
        return std::ranlux48_base(*seed);
    }
    std::ranlux24 ranlux24(const seed_seq_ptr& seed) {
        return std::ranlux24(*seed);
    }
    std::ranlux48 ranlux48(const seed_seq_ptr& seed) {
        return std::ranlux48(*seed);
    }
    std::knuth_b knuth_b(const seed_seq_ptr& seed) {
        return std::knuth_b(*seed);
    }

}
