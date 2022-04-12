# queue-simulator
Single server single queue discrete event simulator (D/D/1)
to build: cc linked_list.c events_queue.c clients_queue.c simulation.c -o simulation (or gcc instead of cc)
usage: 
simulator number_of_clients client_arrival_time client_service_time
or
simulator (without arguments, equivalent to simulator 10000000 6 5 )
