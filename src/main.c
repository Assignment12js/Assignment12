#include "Dijkstra.h"

int main(){
  graph* obj = buildGraph();
  for(size_t i=0; i < readFile().trip_count; i++){
    printf("\n");
  int v = (int) i;
  char ok = readFile().trips[i].type;
  Dijkstra(obj, v, ok);
}
printf("\n");
  return EXIT_SUCCESS;

}
// Here is an example of how you will be working with the output of the parser.
//int main()
//{
    // FILE* file = fopen("data/sample.txt", "r");
    // file_record fr = parse_file(file);
    // fclose(file);

    // Example of working with file_record
    // printf("There are %zu locations.\n", fr.location_count);
    // printf("The locations are named:\n");
    // for (size_t i = 0; i < fr.location_count; i++)
    // {
    //     printf("    %zu: %s\n", i, fr.locations[i].name);
    // }
    //
    // printf("\nThere are %zu roads.\n", fr.road_count);
    // printf("The roads have the following information:\n");
    // for (size_t i = 0; i < fr.road_count; i++)
    // {
    //     printf("    start = %zu; end = %zu; dist = %f; speed = %f\n",
    //              fr.roads[i].start, fr.roads[i].end,
    //              fr.roads[i].distance, fr.roads[i].speed);
    // }
    //
    // printf("\nThere are %zu requested trips\n", fr.trip_count);
    // printf("The trips have the following information:\n");
    // for (size_t i = 0; i < fr.trip_count; i++)
    // {
    //     printf("    start = %zu; end = %zu; type = %c\n",
    //              fr.trips[i].start, fr.trips[i].end, fr.trips[i].type);
    // }
    //
    // file_record_destroy(fr);

    //return EXIT_SUCCESS;
//}
