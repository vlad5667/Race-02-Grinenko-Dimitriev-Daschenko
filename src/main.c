#include "../inc/header.h"

struct queue *create_queue(int size) {
    struct queue *q = malloc(sizeof(*q));
    q->nodes = malloc(sizeof(struct node) * size);
    q->head = -1;
    q->tail = -1;
    return q;
}

bool queue_is_empty(struct queue *q) {
    if (q->tail == -1) {
        return true;
    }
    return false;
}

void push_queue(struct queue *q, struct node n) {
    if (q->head == -1) {
        q->head = 0;
    }
    q->tail++;
    q->nodes[q->tail].pt = n.pt;
    q->nodes[q->tail].dist = n.dist;
}

void pop_queue(struct queue *q) {
    q->head++;
    if (q->head > q->tail) {
        q->head = q->tail = -1;
    }
}

bool isValid(int row, int col, int rows, int cols) {
    return row >= 0 && row < rows && col >= 0 && col < cols;
}

int rowNum[] = {-1, 0, 0, 1};
int colNum[] = {0, -1, 1, 0};

int max_dist = -1;

int BFS(int **mat, struct Point entry, struct Point exit, int rows, int cols) {
    if (!mat[entry.x][entry.y] || !mat[exit.x][exit.y])
        return -1;
    
    int d[rows][cols];
    bool visited[rows][cols];
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            visited[i][j] = false;
            d[i][j] = -1;
        }
    }
    
    visited[entry.x][entry.y] = true;
    d[entry.x][entry.y] = 0;
   
    struct queue *q = create_queue(rows * cols);
     
    struct node s = {entry, 0};
    push_queue(q, s);
    
    int result;
    bool isPathExist = false;
 
    while (!queue_is_empty(q)) {
        struct node curr = q->nodes[q->head];
        struct Point pt = curr.pt;
        
        if (pt.x == exit.x && pt.y == exit.y && !isPathExist) {
            int xx = pt.x, yy = pt.y;
            int dist = curr.dist;
            
            d[pt.x][pt.y] = dist;
            
            mat[xx][yy] = -1;
            
            while (xx != entry.x || yy != entry.y) {
                if (xx == entry.x && yy == entry.y) {
                    break;
                }
                
                if (xx > 0 && d[xx - 1][yy] == dist - 1) {
                    mat[xx - 1][yy] = -1;
                    xx--;
                }
                else if (xx < rows - 1 && d[xx + 1][yy] == dist - 1) {
                    mat[xx + 1][yy] = -1;
                    xx++;
                }
                else if (yy > 0 && d[xx][yy - 1] == dist - 1) {
                    mat[xx][yy - 1] = -1;
                    yy--;
                }
                else if (yy < cols - 1 && d[xx][yy + 1] == dist - 1) {
                    mat[xx][yy + 1] = -1;
                    yy++;
                }
                dist--;
            }
            
            result = curr.dist;
            isPathExist = true;
        }
 
        pop_queue(q);
 
        for (int i = 0; i < 4; i++) {
            int row = pt.x + rowNum[i];
            int col = pt.y + colNum[i];

            if (isValid(row, col, rows, cols) && mat[row][col] && !visited[row][col]) {
                visited[row][col] = true;
                struct node Adjcell = { {row, col}, curr.dist + 1 };
                push_queue(q, Adjcell);
                d[row][col] = curr.dist + 1;
            }
        }
    }
    
    free(q->nodes);
    free(q);
    
    if (isPathExist) {
        int max_x[rows * cols], max_y[rows * cols];
        
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (max_dist < d[i][j]) {
                    max_dist = d[i][j];
                }
            }
        }
        
        int k = 0;
        
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (d[i][j] == max_dist) {
                    max_x[k] = i;
                    max_y[k++] = j;
                }
            }
        }
        
        for (int i = 0; i < k; i++) {
            if (mat[max_x[i]][max_y[i]] == -1) {
                mat[max_x[i]][max_y[i]] = -2;
            }
            else {
                mat[max_x[i]][max_y[i]] = -3;
            }
        }
        return result;
    }
 
    return -1;
}

int main(int argc, char *argv[]) {
    if (argc != 6) {
        mx_printerr("usage: ./way_home [file_name] [x1] [y1] [x2] [y2]\n");
        exit(EXIT_FAILURE);
    }

    int check_file = open(argv[1], O_RDONLY);
    
    if (check_file < 0) {
        mx_printerr("map does not exist\n");
        exit(0);
    }

    char *maze_str = mx_file_to_str(argv[1]);

    if (!mx_strlen(maze_str)) {
        mx_printerr("map does not exist\n");
        exit(EXIT_FAILURE);
    }
    
    int rows = 0, columns = 0;
    
    for (int i = 0, cols = 0; i < mx_strlen(maze_str); i++) {
        if (maze_str[i] != '#' && maze_str[i] != '.' && maze_str[i] != ',' && maze_str[i] != '\n') {
            mx_printerr("map error\n");
            exit(EXIT_FAILURE);
        }
        
        if (maze_str[i] == '\n') {
            rows++;
            columns = cols;
            cols = 0;
        }
        else if (maze_str[i] != ',') {
            cols++;
        }
    }
    
    if (mx_strlen(maze_str) - (columns - 1) * rows - rows != rows * columns) {
        mx_printerr("map error\n");
        exit(EXIT_FAILURE);
    }
    
    int x1 = mx_atoi(argv[2]);
    int y1 = mx_atoi(argv[3]);
    int x2 = mx_atoi(argv[4]);
    int y2 = mx_atoi(argv[5]);

    if (x1 >= columns || y1 >= rows || x2 >= columns || y2 >= rows || x1 < 0 || y1 < 0 || x2 < 0 || y2 < 0) {
        mx_printerr("points are out of map range\n");
        exit(EXIT_FAILURE);
    }
    
    int **mat = (int **)malloc(sizeof(int*) * rows);
    for (int i = 0; i < rows; i++) {
        mat[i] = malloc(sizeof(int) * columns);
    }
    
    for (int i = 0, row = 0, col = 0; i < mx_strlen(maze_str); i++) {
        if (maze_str[i] == '\n') {
            row++;
            col = 0;
        }
        
        if (maze_str[i] == '#') {
            mat[row][col++] = 0;
        }
        else if (maze_str[i] == '.') {
            mat[row][col++] = 1;
        }
    }
    
    if (!mat[y1][x1]) {
        mx_printerr("entry point cannot be an obstacle\n");
        exit(EXIT_FAILURE);
    }

    if (!mat[y2][x2]) {
        mx_printerr("exit point cannot be an obstacle\n");
        exit(EXIT_FAILURE);
    }
    
    struct Point entry = {y1, x1};
    struct Point exit = {y2, x2};

    int dist = BFS(mat, entry, exit, rows, columns);

    if (dist != -1) {
        printf("dist=%d\n", max_dist);
        printf("exit=%d\n", dist);
    }
    else {
        mx_printerr("route not found\n");
    }
    
    int output = open("path.txt", O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (mat[i][j] == -1) {
                write(output, "*", 1);
            }
            else if (mat[i][j] == 1) {
                write(output, ".", 1);
            }
            else if (mat[i][j] == -2) {
                write(output, "X", 1);
            }
            else if (mat[i][j] == -3) {
                write(output, "D", 1);
            }
            else {
                write(output, "#", 1);
            }
        }
        write(output, "\n", 1);
    }
    
    close(output);

    for (int i = 0; i < rows; i++) {
        free(mat[i]);
    }
    free(mat);
    return 0;
}
