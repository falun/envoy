#include "common/dynamo/dynamo_utility.h"

#include <string>

#include "common/stats/stats_impl.h"

#include "spdlog/spdlog.h"

namespace Envoy {
namespace Dynamo {

std::string Utility::buildPartitionStatString(const std::string& stat_prefix,
                                              const std::string& table_name,
                                              const std::string& operation,
                                              const std::string& partition_id) {
  // Use the last 7 characters of the partition id.
  std::string stats_partition_postfix =
      fmt::format(".capacity.{}.__partition_id={}", operation,
                  partition_id.substr(partition_id.size() - 7, partition_id.size()));

  // Calculate how many characters are available for the table prefix.
  size_t remaining_size = Stats::RawStatData::MAX_NAME_SIZE - stats_partition_postfix.size();

  std::string stats_table_prefix = fmt::format("{}table.{}", stat_prefix, table_name);
  // Truncate the table prefix if the current string is too large.
  if (stats_table_prefix.size() > remaining_size) {
    stats_table_prefix = stats_table_prefix.substr(0, remaining_size);
  }
  return fmt::format("{}{}", stats_table_prefix, stats_partition_postfix);
}

} // Dynamo
} // Envoy
