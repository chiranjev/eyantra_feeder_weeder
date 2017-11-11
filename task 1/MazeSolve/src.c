#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define X 25
#define Y 5

/** Structure Name: Maze
 ** Purpose: Used to store maze information retrieved from file.
 **          The maze is represented in form of a 2D array wrapped in a structure.
 **/
struct Maze
{
    int maze_array[Y][Y];
};

/** Structure Name: Graph
 ** Purpose: Used to store the Graph constructed by the buildGraph() function.
 **          The graph is represented in form of a 2D array wrapped in a structure.
 **/
struct Graph
{
    _Bool graph_array[X][X];
};

/** Structure Name: Path_Array
 ** Purpose: Used to store the final path Array constructed by the findPath() function.
 **          The path is represented in form of a 1D array wrapped in a structure.
 **/
struct Path_Array
{
	int path[X];
};

/** Function Name: init_path()
 ** Input: None
 ** Output: Returns a Path_Array structure in which all elements of array are initialized to -1
 ** Example Call: struct Path_Array path = init_path();
 **/

int freePath[4];

void getFreePath(int cell)
{
   int cellWall[4];
   for(int i=0;i<4;i++)
      cellWall[i]=1;
   int temp=cell;
   int i=0;
   while(temp>0)
   {
      cellWall[i++]=1-(temp&1);
      temp>>=1;
   }
   // printf("Cell %d ",cell);
   // for(int i=0;i<4;i++)
   //    printf("%d ",cellWall[i]);
   for(int i=0;i<4;i++)
      freePath[i]=cellWall[i];
}

struct Path_Array init_path()
{
	struct Path_Array path;
	for(int i = 0; i < X; i++)
		path.path[i] = -1;
	return path;
}
/** Function Name: buildGraph()
 ** Input: Accepts a Maze structure as input
 ** Output: Returns a Graph structure as output
 ** Purpose: Constructs a adjacency matrix graph using the maze information passed as argument
 ** Example Call: struct Graph matrix = buildGraph(maze);
 **/
struct Graph buildGraph(struct Maze maze)
{
    struct Graph adj_matrix;

    for(int i=0;i<X;i++)
    {
      for(int j=0;j<X;j++)
         adj_matrix.graph_array[i][j]=0;
   }

    for(int i=0;i<5;i++)
    {
      for(int j=0;j<5;j++)
      {

         int cell=maze.maze_array[i][j];
         getFreePath(cell);
         for(int k=0;k<4;k++)
         {
            if(freePath[k])
            {
               int offset;
               if(k==0)
                  offset=-5;
               else if(k==1)
                  offset=1;
               else if(k==2)
                  offset=5;
               else
                  offset=-1;
               int pos=coord_to_flat(i,j);
               adj_matrix.graph_array[pos][pos+offset]=1;
            }
         }
      }
   }

   for(int i=0;i<25;i++)
   {
      for(int j=0;j<25;j++)
         printf("%d ",adj_matrix.graph_array[i][j]);
      printf("\n");
   }

    return adj_matrix;
}
/** Function Name: findPath
 ** Input: graph - Graph structure
 **        src - start point of path
 **        dst - end point of path
 ** Output: Returns a Path_Array structure which contains the path in the maze from src to dst.
 ** Example Call: struct Path_Array path = findPath(graph, 0, 24)
 **/
struct Path_Array findPath(struct Graph graph, int start, int finish)
{
	struct Path_Array path = init_path();



    return path;
}

/** Function Name: main_function
 ** Input: maze - Maze structure
 **        start - start point of path
 **        finish - end point of path
 ** Output: Returns a Path_Array structure which contains the path in the maze from start to finish.
 ** Logic: This function first constructs a graph from the maze passed as argument and then finds out
 **        path from start to finish. The path is returned as a Path_Array structure.
 ** Example Call: struct Path_Array path = main_function(maze,0,24);
 **/
struct Path_Array main_function(struct Maze maze, int start, int finish)
{
   // for(int i=0;i<5;i++)
   // {
   //    for(int j=0;j<5;j++)
   //    {
   //       printf("%d ",maze.maze_array[i][j]);
   //    }
   //    printf("\n");
   // }

   // for(int i=0;i<5;i++)
   // {
   //    for(int j=0;j<5;j++)
   //    {
   //       getFreePath(maze.maze_array[i][j]);
   //    }
   //    printf("\n");
   // }

    struct Graph adjacency_matrix = buildGraph(maze);
    struct Path_Array path = findPath(adjacency_matrix, start, finish);
	return path;
}

/** Function Name: parseFile
 ** Input: fileName -  a string containing the relative path of the test case
 ** Output: Returns a Maze structure.
 ** Logic: This function reads the the specified txt file in the TestCases folder and constructs
           a Maze structure from the information.
 ** Example Call: struct Maze maze = parseFile("..\\..\\Task 1A\\TestCases\\maze_4.txt");
 **/
struct Maze parseFile(char fileName[70])
{
    FILE *fp;
    char buff[100];
    int i = 0, j = 0;
    struct Maze maze;
    fp = fopen(fileName,"r");
    fgets(buff, 100, (FILE*)fp);
    char *token = strtok(buff," ");
    while(token != NULL)
    {
        int temp = atoi(token);
        maze.maze_array[i][j] = temp;
        j++;
        if(j == 5)
        {
            i++;
            j = 0;
        }
        token = strtok(NULL, " ");
    }
    return maze;
}

/**************************************** Utility Functions *********************************/

/** Function Name: coord_to_flat
 ** Input: Accepts coordinates x and y of maze cell as input.
 ** Logic: The maze structure is represented as a 2D array. The cells of the maze can be numbered
 **        in a sequential form (0,1,2,3,4,5....23,24) so that it is easier to construct a graph.
 **        This function accepts the maze cell coordinates and returns an integer.
 ** Output: Returns an integer representing the position of maze cell relative to the start position.
 ** Example Call: coord_to_flat()
 **/
int coord_to_flat(int x, int y)
{
    return x*Y + y;
}

/**************************************** Utility Functions *********************************/
