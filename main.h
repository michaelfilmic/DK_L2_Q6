
/*
 * 
 * Simulation_Run of A Single Server Queueing System
 * 
 * Copyright (C) 2014 Terence D. Todd Hamilton, Ontario, CANADA,
 * todd@mcmaster.ca
 * 
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 3 of the License, or (at your option)
 * any later version.
 * 
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 * 
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 * 
 */

/******************************************************************************/

#ifndef _MAIN_H_
#define _MAIN_H_

/******************************************************************************/

#include "simlib.h"
#include "simparameters.h"

/******************************************************************************/

typedef struct _simulation_run_data_ 
{
  double p12_cutoff;
  Fifoqueue_Ptr buffer;
  Server_Ptr link;
  double packet_arrival_rate;
  long int blip_counter;
  long int arrival_count;
  long int number_of_packets_processed;
  double accumulated_delay;
  unsigned random_seed;

  Fifoqueue_Ptr buffer_2;
  Server_Ptr link_2;
  double packet_arrival_rate_2;
  long int blip_counter_2;
  long int arrival_count_2;
  long int number_of_packets_processed_2;
  double accumulated_delay_2;
  unsigned random_seed_2;

  Fifoqueue_Ptr buffer_3;
  Server_Ptr link_3;
  double packet_arrival_rate_3;
  long int blip_counter_3;
  long int arrival_count_3;
  long int number_of_packets_processed_3;
  double accumulated_delay_3;
  unsigned random_seed_3;
} Simulation_Run_Data, * Simulation_Run_Data_Ptr;

typedef enum {XMTTING, WAITING} Packet_Status;

typedef struct _packet_ 
{
  double arrive_time;
  double service_time;
  int source_id;
  int destination_id;
  Packet_Status status;
} Packet, * Packet_Ptr;

/*
 * Function prototypes
 */

int
main(void);

/******************************************************************************/

#endif /* main.h */


