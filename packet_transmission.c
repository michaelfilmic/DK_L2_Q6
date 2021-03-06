
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
#include "trace.h"
#include "main.h"
#include "output.h"
#include "packet_transmission.h"

/******************************************************************************/

/*
 * This function will schedule the end of a packet transmission at a time given
 * by event_time. At that time the function "end_packet_transmission" (defined
 * in packet_transmissionl.c) is executed. A packet object is attached to the
 * event and is recovered in end_packet_transmission.c.
 */

long
schedule_end_packet_transmission_event(Simulation_Run_Ptr simulation_run,
				       double event_time,
				       Server_Ptr link)
{
  Event event;

  //TRACE(printf("MM_debug in schedule_end_packet_transmission_event.\n");)
  event.description = "data Packet Xmt End";
  event.function = end_packet_transmission_event;
  event.attachment = (void *) link;

  return simulation_run_schedule_event(simulation_run, event, event_time);
}

long
schedule_end_packet_transmission_event_sw2(Simulation_Run_Ptr simulation_run,
				       double event_time,
				       Server_Ptr link)
{
  Event event;

  //TRACE(printf("MM_debug in schedule_end_packet_transmission_event.\n");)
  event.description = "voice Packet Xmt End";
  event.function = end_packet_transmission_event_sw2;
  event.attachment = (void *) link;

  return simulation_run_schedule_event(simulation_run, event, event_time);
}

/******************************************************************************/

/*
 * This is the event function which is executed when the end of a packet
 * transmission event occurs. It updates its collected data then checks to see
 * if there are other packets waiting in the fifo queue. If that is the case it
 * starts the transmission of the next packet.
 */

void
end_packet_transmission_event(Simulation_Run_Ptr simulation_run, void * link)
{
  Simulation_Run_Data_Ptr data;
  Packet_Ptr this_packet, next_packet;

  TRACE(printf("data End Of Packet.\n"););

  data = (Simulation_Run_Data_Ptr) simulation_run_data(simulation_run);

  /* 
   * Packet transmission is finished. Take the packet off the data link.
   */

  this_packet = (Packet_Ptr) server_get(link);

  /* Collect statistics. */
  data->number_of_packets_processed++;
  data->accumulated_delay += simulation_run_get_time(simulation_run) - 
    this_packet->arrive_time;

  /* Output activity blip every so often. */
  output_progress_msg_to_screen(simulation_run);

  /* This packet is done ... give the memory back. */
  xfree((void *) this_packet);

  /* 
   * See if there is are packets waiting in the buffer. If so, take the next one
   * out and transmit it immediately.
  */
#ifdef RUN_SAME_AS_Q5
  if(fifoqueue_size(data->buffer) > 0) {
    next_packet = (Packet_Ptr) fifoqueue_get(data->buffer);
    start_transmission_on_link(simulation_run, next_packet, link);
  }
#else
  if(fifoqueue_size(data->buffer_2) > 0) {//if voice not empty
    next_packet = (Packet_Ptr) fifoqueue_get(data->buffer_2);
    start_transmission_on_link_sw2(simulation_run, next_packet, link);
  }
  else if(fifoqueue_size(data->buffer) > 0) {//if data not empty
    next_packet = (Packet_Ptr) fifoqueue_get(data->buffer);
    start_transmission_on_link(simulation_run, next_packet, link);
  }
#endif
}

void
end_packet_transmission_event_sw2(Simulation_Run_Ptr simulation_run, void * link)
{
  Simulation_Run_Data_Ptr data;
  Packet_Ptr this_packet, next_packet;

  TRACE(printf("voice End Of Packet.\n"););

  data = (Simulation_Run_Data_Ptr) simulation_run_data(simulation_run);

  /* 
   * Packet transmission is finished. Take the packet off the data link.
   */

  this_packet = (Packet_Ptr) server_get(link);

  /* Collect statistics. */
  data->number_of_packets_processed_2++;
  data->accumulated_delay_2 += simulation_run_get_time(simulation_run) - 
    this_packet->arrive_time;

  /* Output activity blip every so often. */
  output_progress_msg_to_screen_sw2(simulation_run);

  /* This packet is done ... give the memory back. */
  xfree((void *) this_packet);

  /* 
   * See if there is are packets waiting in the buffer. If so, take the next one
   * out and transmit it immediately.
  */


#ifdef RUN_SAME_AS_Q5
  if(fifoqueue_size(data->buffer_2) > 0) {
    next_packet = (Packet_Ptr) fifoqueue_get(data->buffer_2);
    start_transmission_on_link_sw2(simulation_run, next_packet, link);
  }
#else
  if(fifoqueue_size(data->buffer_2) > 0) {//if voice not empty
    next_packet = (Packet_Ptr) fifoqueue_get(data->buffer_2);
    start_transmission_on_link_sw2(simulation_run, next_packet, link);
  }
  else if(fifoqueue_size(data->buffer) > 0) {//if data not empty
    next_packet = (Packet_Ptr) fifoqueue_get(data->buffer);
    start_transmission_on_link(simulation_run, next_packet, link);
  }
#endif
}

/*
 * This function ititiates the transmission of the packet passed to the
 * function. This is done by placing the packet in the server. The packet
 * transmission end event for this packet is then scheduled.
 */

void
start_transmission_on_link(Simulation_Run_Ptr simulation_run, 
			   Packet_Ptr this_packet,
			   Server_Ptr link)
{
  TRACE(printf("data Start Of Packet.\n");)

  server_put(link, (void*) this_packet);
  this_packet->status = XMTTING;

  /* Schedule the end of packet transmission event. */
  schedule_end_packet_transmission_event(simulation_run,
	 simulation_run_get_time(simulation_run) + this_packet->service_time,
	 (void *) link);
}

void
start_transmission_on_link_sw2(Simulation_Run_Ptr simulation_run, 
			   Packet_Ptr this_packet,
			   Server_Ptr link)
{
  TRACE(printf("voice Start Of Packet.\n");)

  server_put(link, (void*) this_packet);
  this_packet->status = XMTTING;

  /* Schedule the end of packet transmission event. */
  schedule_end_packet_transmission_event_sw2(simulation_run,
	 simulation_run_get_time(simulation_run) + this_packet->service_time,
	 (void *) link);
}

/*
 * Get a packet transmission time. For now it is a fixed value defined in
 * simparameters.h
 */

double get_packet_transmission_time(void)
{
  return (exponential_generator(PACKET_XMT_TIME));
  //return (1/(exponential_generator((double) 1/PACKET_XMT_TIME)));
  //return ((exponential_generator((double) 1/PACKET_XMT_TIME)));

}

double get_packet_transmission_time_sw2(void)
{
  return ((double) PACKET_XMT_TIME_VOICE);
}


