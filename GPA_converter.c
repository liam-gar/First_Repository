#include<stdlib.h>
#include<stdio.h>
#include<string.h>

int twelve(int GPA){
    if (GPA<50){
        return 0;
    }
    else if (50<=GPA,GPA<=52){
        return 1;
    }
    else if (53<=GPA,GPA<=56){
        return 2;
    }
    else if (57<=GPA,GPA<=59){
        return 3;
    }
    else if (60<=GPA,GPA<=62){
        return 4;
    }
    else if (63<=GPA,GPA<=66){
        return 5;
    }
    else if (67<=GPA,GPA<=69){
        return 6;
    }
    else if (70<=GPA,GPA<=72){
        return 7;
    }
    else if (73<=GPA,GPA<=76){
        return 8;
    }
    else if (77<=GPA,GPA<=79){
        return 9;
    }
    else if (80<=GPA,GPA<=84){
        return 10;
    }
    else if (85<=GPA,GPA<=89){
        return 11;
    }
    else if (90<=GPA){
        return 12;
    }
}

double four(int GPA){
    if (GPA<50){
        return 0;
    }
    else if (50<=GPA,GPA<=52){
        return 0.7;
    }
    else if (53<=GPA,GPA<=56){
        return 1.0;
    }
    else if (57<=GPA,GPA<=59){
        return 1.3;
    }
    else if (60<=GPA,GPA<=62){
        return 1.7;
    }
    else if (63<=GPA,GPA<=66){
        return 2;
    }
    else if (67<=GPA,GPA<=69){
        return 2.3;
    }
    else if (70<=GPA,GPA<=72){
        return 2.7;
    }
    else if (73<=GPA,GPA<=76){
        return 3.0;
    }
    else if (77<=GPA,GPA<=79){
        return 3.3;
    }
    else if (80<=GPA,GPA<=84){
        return 3.7;
    }
    else if (85<=GPA,GPA<=89){
        return 3.9;
    }
    else if (90<=GPA){
        return 4.0;
    }
}

char letter (int GPA){
    if (GPA<50){
        return 'F';
    }
    else if (50<=GPA,GPA<=59){
        return 'D';
    }
    else if (60<=GPA,GPA<=69){
        return 'C';
    }
    else if (70<=GPA,GPA<=79){
        return 'B';
    }
    else if (80<=GPA){
        return 'A';
    }
}

char sign(int GPA){
    if (GPA<50){
        return 0;
    }
    else if (50<=GPA,GPA<=52){
        return '-';
    }
    else if (53<=GPA,GPA<=56){
        return 0;
    }
    else if (57<=GPA,GPA<=59){
        return '+';
    }
    else if (60<=GPA,GPA<=62){
        return '-';
    }
    else if (63<=GPA,GPA<=66){
        return 0;
    }
    else if (67<=GPA,GPA<=69){
        return '+';
    }
    else if (70<=GPA,GPA<=72){
        return '-';
    }
    else if (73<=GPA,GPA<=76){
        return 0;
    }
    else if (77<=GPA,GPA<=79){
        return '+';
    }
    else if (80<=GPA,GPA<=84){
        return '-';
    }
    else if (85<=GPA,GPA<=89){
        return 0;
    }
    else if (90<=GPA){
        return '+';
    }
}

void main(){
    int percentage;
    printf("\nEnter your percentage grade : ");
    scanf("%d",&percentage);
    printf("\nYour grade on a 12 point scale : %d\nYour letter grade is : %c%c\nYour grade on a 4 point scale : %.1lf\n ",twelve(percentage),letter(percentage),sign(percentage),four(percentage));
}