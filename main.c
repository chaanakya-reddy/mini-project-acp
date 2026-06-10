#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define ROWS 30
#define COLS 70
#define MAX 150

/* ---------------- TYPES ---------------- */

typedef enum {
    LINE = 1,
    RECT,
    FILL_RECT,
    TRI,
    CIRCLE,
    DLINE,
    TLINE
} Type;

typedef struct {
    int id;
    Type type;
    int x1,y1,x2,y2,x3,y3;
    int r;
    int active;
} Shape;

/* ---------------- GLOBALS ---------------- */

char canvas[ROWS][COLS];
Shape shapes[MAX];
int count = 0;

/* ---------------- CANVAS ---------------- */

void initCanvas() {
    for(int i=0;i<ROWS;i++)
        for(int j=0;j<COLS;j++)
            canvas[i][j] = '_';
}

void setPixel(int x,int y) {
    if(x>=0 && x<COLS && y>=0 && y<ROWS)
        canvas[y][x] = '*';
}

void printCanvas() {
    printf("\n   ");
    for(int j=0;j<COLS;j++) printf("%d", j%10);
    printf("\n");

    for(int i=0;i<ROWS;i++) {
        printf("%2d ", i);
        for(int j=0;j<COLS;j++)
            printf("%c", canvas[i][j]);
        printf("\n");
    }
}

/* ---------------- LINE ---------------- */

void drawLine(int x1,int y1,int x2,int y2) {
    int dx = abs(x2-x1);
    int dy = abs(y2-y1);
    int sx = (x1<x2)?1:-1;
    int sy = (y1<y2)?1:-1;
    int err = dx - dy;

    while(1) {
        setPixel(x1,y1);
        if(x1==x2 && y1==y2) break;

        int e2 = 2*err;

        if(e2 > -dy) { err -= dy; x1 += sx; }
        if(e2 < dx)  { err += dx; y1 += sy; }
    }
}

/* ---------------- THICK LINE ---------------- */

void drawThickLine(int x1,int y1,int x2,int y2) {
    for(int i=-1;i<=1;i++)
        for(int j=-1;j<=1;j++)
            drawLine(x1+i,y1+j,x2+i,y2+j);
}

/* ---------------- DASHED LINE ---------------- */

void drawDashedLine(int x1,int y1,int x2,int y2) {
    int dx = abs(x2-x1);
    int dy = abs(y2-y1);
    int sx = (x1<x2)?1:-1;
    int sy = (y1<y2)?1:-1;
    int err = dx - dy;
    int c = 0;

    while(1) {
        if(c % 2 == 0)
            setPixel(x1,y1);

        c++;

        if(x1==x2 && y1==y2) break;

        int e2 = 2*err;

        if(e2 > -dy) { err -= dy; x1 += sx; }
        if(e2 < dx)  { err += dx; y1 += sy; }
    }
}

/* ---------------- RECT ---------------- */

void drawRect(int x1,int y1,int x2,int y2) {
    drawLine(x1,y1,x2,y1);
    drawLine(x2,y1,x2,y2);
    drawLine(x2,y2,x1,y2);
    drawLine(x1,y2,x1,y1);
}

/* ---------------- FILLED RECT ---------------- */

void drawFillRect(int x1,int y1,int x2,int y2) {
    for(int i=y1;i<=y2;i++)
        for(int j=x1;j<=x2;j++)
            setPixel(j,i);
}

/* ---------------- TRIANGLE ---------------- */

void drawTri(int x1,int y1,int x2,int y2,int x3,int y3) {
    drawLine(x1,y1,x2,y2);
    drawLine(x2,y2,x3,y3);
    drawLine(x3,y3,x1,y1);
}

/* ---------------- CIRCLE ---------------- */

void drawCircle(int cx,int cy,int r) {
    int x=0,y=r;
    int d=1-r;

    while(x<=y) {
        setPixel(cx+x,cy+y);
        setPixel(cx-x,cy+y);
        setPixel(cx+x,cy-y);
        setPixel(cx-x,cy-y);

        setPixel(cx+y,cy+x);
        setPixel(cx-y,cy+x);
        setPixel(cx+y,cy-x);
        setPixel(cx-y,cy-x);

        x++;
        if(d<0) d += 2*x+1;
        else { y--; d += 2*(x-y)+1; }
    }
}

/* ---------------- REDRAW ---------------- */

void redraw() {
    initCanvas();

    for(int i=0;i<count;i++) {
        if(!shapes[i].active) continue;

        Shape s = shapes[i];

        switch(s.type) {
            case LINE:
                drawLine(s.x1,s.y1,s.x2,s.y2);
                break;

            case RECT:
                drawRect(s.x1,s.y1,s.x2,s.y2);
                break;

            case FILL_RECT:
                drawFillRect(s.x1,s.y1,s.x2,s.y2);
                break;

            case TRI:
                drawTri(s.x1,s.y1,s.x2,s.y2,s.x3,s.y3);
                break;

            case CIRCLE:
                drawCircle(s.x1,s.y1,s.r);
                break;

            case DLINE:
                drawDashedLine(s.x1,s.y1,s.x2,s.y2);
                break;

            case TLINE:
                drawThickLine(s.x1,s.y1,s.x2,s.y2);
                break;
        }
    }
}

/* ---------------- ADD ---------------- */

void addShape() {
    if(count>=MAX) return;

    Shape s;
    s.id = count;
    s.active = 1;

    int temp;
    printf("\n1.Line 2.Rect 3.FillRect 4.Triangle 5.Circle 6.Dashed 7.Thick\nChoice: ");
    scanf("%d",&temp);
    s.type = (Type)temp;

    switch(s.type) {
        case LINE:
        case DLINE:
        case TLINE:
        case RECT:
        case FILL_RECT:
            printf("Enter x1 y1 x2 y2: ");
            scanf("%d%d%d%d",&s.x1,&s.y1,&s.x2,&s.y2);
            break;

        case TRI:
            printf("Enter x1 y1 x2 y2 x3 y3: ");
            scanf("%d%d%d%d%d%d",
                &s.x1,&s.y1,&s.x2,&s.y2,&s.x3,&s.y3);
            break;

        case CIRCLE:
            printf("Enter cx cy r: ");
            scanf("%d%d%d",&s.x1,&s.y1,&s.r);
            break;
    }

    shapes[count++] = s;
    redraw();
}

/* ---------------- LIST ---------------- */

void listShapes() {
    printf("\n--- OBJECTS ---\n");
    for(int i=0;i<count;i++)
        if(shapes[i].active)
            printf("ID:%d Type:%d\n",shapes[i].id,shapes[i].type);
}

/* ---------------- DELETE ---------------- */

void deleteShape() {
    listShapes();

    int id;
    printf("Enter ID: ");
    scanf("%d",&id);

    if(id>=0 && id<count)
        shapes[id].active = 0;

    redraw();
}

/* ---------------- MODIFY ---------------- */

void modifyShape() {
    listShapes();

    int id;
    printf("Enter ID: ");
    scanf("%d",&id);

    if(id<0 || id>=count || !shapes[id].active)
        return;

    Shape *s = &shapes[id];

    printf("Enter new values:\n");

    switch(s->type) {
        case LINE:
        case DLINE:
        case TLINE:
        case RECT:
        case FILL_RECT:
            scanf("%d%d%d%d",&s->x1,&s->y1,&s->x2,&s->y2);
            break;

        case TRI:
            scanf("%d%d%d%d%d%d",
                &s->x1,&s->y1,&s->x2,&s->y2,&s->x3,&s->y3);
            break;

        case CIRCLE:
            scanf("%d%d%d",&s->x1,&s->y1,&s->r);
            break;
    }

    redraw();
}

/* ---------------- SAVE ---------------- */

void saveFile() {
    FILE *f = fopen("data.bin","wb");
    for(int i=0;i<count;i++)
        fwrite(&shapes[i],sizeof(Shape),1,f);
    fclose(f);
}

/* ---------------- LOAD ---------------- */

void loadFile() {
    FILE *f = fopen("data.bin","rb");
    if(!f) return;

    count = 0;
    while(fread(&shapes[count],sizeof(Shape),1,f))
        count++;

    fclose(f);
    redraw();
}

/* ---------------- MAIN ---------------- */

int main() {
    int ch;
    initCanvas();

    while(1) {
        printf("\n1.Add 2.Delete 3.Modify 4.Show 5.List 6.Save 7.Load 8.Exit\n");
        scanf("%d",&ch);

        switch(ch) {
            case 1: addShape(); break;
            case 2: deleteShape(); break;
            case 3: modifyShape(); break;
            case 4: printCanvas(); break;
            case 5: listShapes(); break;
            case 6: saveFile(); break;
            case 7: loadFile(); break;
            case 8: return 0;
        }
    }
}
