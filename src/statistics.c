#include "ft_ping.h"

void  update_statistics(t_statistics* stats, double rtt)
{
  stats->received += 1;
  if (stats->min == 0 && stats->max == 0 && stats->sum == 0 && stats->sum_sq == 0)
  {
    stats->min = rtt;
    stats->max = rtt;
    stats->sum = rtt;
    stats->sum_sq = rtt * rtt;
  }
  else
  {
    if (rtt < stats->min)
      stats->min = rtt;
    if (rtt > stats->max)
      stats->max = rtt;
    stats->sum += rtt;
    stats->sum_sq += rtt * rtt;
  }
}

void  final_statistics(t_statistics* stats)
{
  stats->percentage = 100 - (100 * stats->received / stats->transmitted);
  stats->avg = stats->sum / stats->received;
  stats->stddev = sqrt((stats->sum_sq / stats->received) - (stats->avg * stats->avg)) ;
}

