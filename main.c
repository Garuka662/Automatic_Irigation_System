sbit EN at P0_0_bit;
sbit RW at P0_1_bit;
sbit RS at P0_2_bit;

sbit WR at P3_0_bit;
sbit INTR at P3_1_bit;
sbit RD at P3_2_bit;
sbit OUT at P3_4_bit;

void lcdcmd(unsigned char value);
void lcddata(unsigned char value);
void lcdinit();

unsigned char itoc(int i);

void main() {

     unsigned char value,k,value1;
     int temp[3]={0,0,0},i,j=0;
     unsigned char a[]="MOISTURE";
     unsigned char b[]="   MOTOR";
     unsigned char n[]="ON ";
     unsigned char f[]="OFF";
     p0=0x00;
     p2=0x00;
     p1=255;
     lcdinit();
     WR = 1;
     INTR = 1;
     RD = 1;
     
     while(a[j]!='\0')
     {
             lcddata(a[j]);
             delay_ms(20);
             j++;
     }
     j=0;
     lcdcmd(0x3C);
     delay_ms(250);
     lcdcmd(0xC0);
     delay_ms(250);
     while(b[j]!='\0')
     {
             lcddata(b[j]);
             delay_ms(20);
             j++;
     }
     
     while(1)
     {
             WR = 0;
             WR = 1;
             

             while(INTR == 1);
             
             RD = 0;
             value = p1;
             value=255-value;
             value1=value;
             i=2;
             while(value!=0)
             {
                        temp[i] = value%10;
                        value = value/10;
                        i--;
             }
             j=0;
             lcdcmd(0x8A);
             delay_ms(250);
             while(j<=2)
             {
                     k=itoc(temp[j]);
                     lcddata(k);
                     delay_ms(10);
                     temp[j]=0;
                     j++;
             }
             j=0;
             if(value1>150)
             {
                     OUT=1;
                     lcdcmd(0xCA);
                     delay_ms(250);
                     while(n[j]!='\0')
                     {
                             lcddata(n[j]);
                             delay_ms(20);
                             j++;
                     }
             }
             else
             {
                     OUT=0;
                     lcdcmd(0xCA);
                     delay_ms(250);
                     while(f[j]!='\0')
                     {
                             lcddata(f[j]);
                             delay_ms(20);
                             j++;
                     }

             }
             RD = 1;
     }
}

void lcdcmd(unsigned char value)
{
     P2=value;
     RS=0;
     RW=0;
     EN=1;
     delay_ms(5);
     EN=0;
     return;
}

void lcddata(unsigned char value)
{
     P2=value;
     RS=1;
     RW=0;
     EN=1;
     delay_ms(5);
     EN=0;
     return;

}

void lcdinit()
{
     lcdcmd(0x38);
     delay_ms(250);
     lcdcmd(0x0C);
     delay_ms(250);
     lcdcmd(0x01);
     delay_ms(250);
     lcdcmd(0x80);
     delay_ms(250);
}

unsigned char itoc(int i)
{
     switch(i)
     {
              case 0: return '0'; break;
              case 1: return '1'; break;
              case 2: return '2'; break;
              case 3: return '3'; break;
              case 4: return '4'; break;
              case 5: return '5'; break;
              case 6: return '6'; break;
              case 7: return '7'; break;
              case 8: return '8'; break;
              case 9: return '9'; break;
     }
}
