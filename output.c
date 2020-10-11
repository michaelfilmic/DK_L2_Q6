
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

#include <stdio.h>
#include "simparameters.h"
#include "main.h"
#include "output.h"

/******************************************************************************/

/*
 * This function outputs a progress message to the screen to indicate this are
 * working.
 */

void
output_progress_msg_to_screen(Simulation_Run_Ptr simulation_run)
{
  double percentage_done;
  Simulation_Run_Data_Ptr data;

  data = (Simulation_Run_Data_Ptr) simulation_run_data(simulation_run);

  data->blip_counter++;

  if((data->blip_counter >= BLIPRATE)
     ||
     (data->number_of_packets_processed >= RUNLENGTH)) {

    data->blip_counter = 0;

    percentage_done =
      100 * (double) data->number_of_packets_processed/RUNLENGTH;

    printf("%3.0f%% ", percentage_done);

    printf("data Successfully Xmtted Pkts  = %ld (Arrived Pkts = %ld) \n", 
	   data->number_of_packets_processed, data->arrival_count);

    fflush(stdout);
  }

}

void
output_progress_msg_to_screen_sw2(Simulation_Run_Ptr simulation_run)
{
  double percentage_done;
  Simulation_Run_Data_Ptr data;

  data = (Simulation_Run_Data_Ptr) simulation_run_data(simulation_run);

  data->blip_counter_2++;

  if((data->blip_counter_2 >= BLIPRATE)
     ||
     (data->number_of_packets_processed_2 >= RUNLENGTH)) {

    data->blip_counter_2 = 0;

    percentage_done =
      100 * (double) data->number_of_packets_processed_2/RUNLENGTH;

    printf("%3.0f%% ", percentage_done);

    printf("voice Successfully Xmtted Pkts  = %ld (Arrived Pkts = %ld) \n", 
	   data->number_of_packets_processed_2, data->arrival_count_2);

    fflush(stdout);
  }

}

void
output_progress_msg_to_screen_sw3(Simulation_Run_Ptr simulation_run)
{
  double percentage_done;
  Simulation_Run_Data_Ptr data;

  data = (Simulation_Run_Data_Ptr) simulation_run_data(simulation_run);

  data->blip_counter_3++;

  if((data->blip_counter_3 >= BLIPRATE)
     ||
     (data->number_of_packets_processed_3 >= RUNLENGTH)) {

    data->blip_counter_3 = 0;

    percentage_done =
      100 * (double) data->number_of_packets_processed_3/RUNLENGTH;

    printf("%3.0f%% ", percentage_done);

    printf("SW3 Successfully Xmtted Pkts  = %ld (Arrived Pkts = %ld) \n", 
	   data->number_of_packets_processed_3, data->arrival_count_3);

    fflush(stdout);
  }

}

/*
 * When a simulation_run run is completed, this function outputs various
 * collected statistics on the screen.
 */

void
output_results(Simulation_Run_Ptr simulation_run)
{
  double xmtted_fraction;
  Simulation_Run_Data_Ptr data;

  data = (Simulation_Run_Data_Ptr) simulation_run_data(simulation_run);

  printf("\n");
  printf("data: \n");
  printf("Random Seed = %d \n", data->random_seed);
  printf("Packet arrival count = %ld \n", data->arrival_count);

  xmtted_fraction = (double) data->number_of_packets_processed /
    data->arrival_count;

  printf("Transmitted packet count  = %ld (Service Fraction = %.5f)\n",
	 data->number_of_packets_processed, xmtted_fraction);

  printf("Arrival rate = %.3f packets/second \n", (double) data->packet_arrival_rate);

  printf("Mean Delay (msec) = %f \n",
	 1e3*data->accumulated_delay/data->number_of_packets_processed);

  printf("\n");

  #ifndef NO_CSV_OUTPUT
  /*
  // create a csv file
  FILE* fp;
  char data_set_name[] = "./Q2.csv";

  //file IO
  fp = fopen(data_set_name, "a");
  //cell/element name/type

  //fprintf(fp, ("Random Seed,"));
  fprintf(fp, "%d, ", data->random_seed);

  //fprintf(fp, ("Packet arrival count,"));
  fprintf(fp, "%ld, ", data->arrival_count);

  //fprintf(fp, ("Transmitted packet count ,"));
  fprintf(fp, "%ld,", data->number_of_packets_processed);

  //fprintf(fp, ("Service Fraction ,"));
  fprintf(fp, "%.5f,", xmtted_fraction);

  //fprintf(fp, ("Arrival rate,"));
  fprintf(fp, "%.3f, ", (double) data->packet_arrival_rate);

  //fprintf(fp, ("Mean Delay (msec),"));
  fprintf(fp, "%.2f, ",
	 1e3*data->accumulated_delay/data->number_of_packets_processed);

  fprintf(fp, "\n");

  fclose(fp);
  */
  #endif
}

void
output_results_sw2(Simulation_Run_Ptr simulation_run)
{
  double xmtted_fraction;
  Simulation_Run_Data_Ptr data;

  data = (Simulation_Run_Data_Ptr) simulation_run_data(simulation_run);

  printf("\n");
  printf("voice: \n");
  printf("Random Seed = %d \n", data->random_seed_2);
  printf("Packet arrival count = %ld \n", data->arrival_count_2);

  xmtted_fraction = (double) data->number_of_packets_processed_2 /
    data->arrival_count_2;

  printf("Transmitted packet count  = %ld (Service Fraction = %.5f)\n",
	 data->number_of_packets_processed_2, xmtted_fraction);

  printf("Arrival rate = %.3f packets/second \n", (double) data->packet_arrival_rate_2);

  printf("Mean Delay (msec) = %f \n",
	 1e3*data->accumulated_delay_2/data->number_of_packets_processed_2);

  printf("\n");
}

void
output_results_sw3(Simulation_Run_Ptr simulation_run)
{
  double xmtted_fraction;
  Simulation_Run_Data_Ptr data;

  data = (Simulation_Run_Data_Ptr) simulation_run_data(simulation_run);

  printf("\n");
  printf("SW3: \n");
  printf("Random Seed = %d \n", data->random_seed_3);
  printf("Packet arrival count = %ld \n", data->arrival_count_3);

  xmtted_fraction = (double) data->number_of_packets_processed_3 /
    data->arrival_count_3;

  printf("Transmitted packet count  = %ld (Service Fraction = %.5f)\n",
	 data->number_of_packets_processed_3, xmtted_fraction);

  printf("Arrival rate = %.3f packets/second \n", (double) data->packet_arrival_rate_3);

  printf("Mean Delay (msec) = %f \n",
	 1e3*data->accumulated_delay_3/data->number_of_packets_processed_3);

  printf("\n");
}

