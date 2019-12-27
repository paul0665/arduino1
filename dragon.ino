// ------------------------------------------------
// 範例: MatrixLED_heart.ino
// 功能: MatrixLED 全彩8x8顯示 - 畫面顏色不間斷循環顯示 
// Support: Atmel SAM3X8E  
//
// 接線說明  
// +------------+----------+------------+
// | Arduino    | IO編號   | 點矩陣模組 |
// +------------+----------+------------+
// | D22 ~ D29  | 49~56    | R1 ~ R8    | 
// +------------+----------+------------+
// | D30 ~ D37  | 57~64    | G1 ~ G8    | 
// +------------+----------+------------+
// | D38 ~ D45  | 65~72    | B1 ~ B8    | 
// +------------+----------+------------+
// | D46 ~ D48  | 73~75    | S0 ~ S2    | 
// +------------+----------+------------+
// | D49        | 76       | EN         | 
// +------------+----------+------------+
//
// Date: 2018-11-08  by wangwang
//-------------------------------------------------

int DATA_R0   = 22;   
int DATA_G0   = 30;
int DATA_B0   = 38;
int S0        = 46;
int S1        = 47;
int S2        = 48;
int EN        = 49;

/*====圖片定義===================*/
unsigned long NUM_LED[10][8] =
{
   {0xffffff, 0xffffff, 0x7fff7f, 0xffffff, 0xffffff, 0x7fff7f, 0xffffff, 0xffffff},   //Section.1
   {0xffffff, 0xbfffbf, 0x3fff3f, 0xffffff, 0xbfffbf, 0x3fff3f, 0xffffff, 0xffffff},   //Section.2
   {0xdfffdf, 0x9fff9f, 0x1fff1f, 0xdfffdf, 0x9fff9f, 0x1fff1f, 0xdfffdf, 0xffffff},   //Section.3
   {0xcfffcf, 0x8fff8f, 0x0fff0f, 0xcfffcf, 0x8fff8f, 0x0fff0f, 0xcfffcf, 0xefffef},   //Section.4
   {0xc7ffc7, 0x8fff8f, 0x07ff07, 0xc7ffc7, 0x87ff87, 0x07ff07, 0xc7ffc7, 0xefffef},   //Section.5
   {0xc7ffc7, 0x8fff8f, 0x07ff07, 0xc7ffc7, 0x83ff83, 0x03ff03, 0xc3ffc3, 0xebffeb},   //Section.6
   {0xc7ffc7, 0x8fff8f, 0x07ff07, 0xc7ffc7, 0x81ff81, 0x03ff03, 0xc1ffc1, 0xebffeb},   //Section.7
   {0xc7ffc7, 0x8fff8f, 0x07ff07, 0xc7ffc7, 0x80ff80, 0x02ff02, 0xc0ffc0, 0xebffeb},   //Section.8
   {0xebffeb, 0x00ff00, 0x82ff82, 0xc0ffc0, 0xc7ffc7, 0xc7ffc7, 0x0fff0f, 0x87ff87},   //Section.9
   {0xebffeb, 0xc0ffc0, 0x02ff02, 0x80ff80, 0x07ff07, 0x87ff87, 0xcfffcf, 0xc7ffc7},   //Section.10
}; 

   
unsigned int count;
unsigned char page_num;   

void setup()
{                
   unsigned int i;
 
   pinMode(EN, OUTPUT);
   pinMode(S0, OUTPUT);
   pinMode(S1, OUTPUT);
   pinMode(S2, OUTPUT);         

   for (i = 0; i < 24; i++)
   {
      pinMode(DATA_R0 + i, OUTPUT);
      digitalWrite(DATA_R0 + i, HIGH);    
   }   

   digitalWrite(EN, LOW);   
   count    = 0; 
   page_num = 0; 
}

void loop()
{
   unsigned long i,j;
           
   for (i = 0; i < 8; i++)                   // 更換掃描線
   {
      digitalWrite(EN, LOW);                 // 關閉掃描線         
      delayMicroseconds(150);
               
      // 資料轉Bit輸出   
      for (j = 0; j < 24; j++)
      {                        
         if ((NUM_LED[page_num][i] & (0x800000 >> j)) == 0)
            digitalWrite( DATA_R0 + j, LOW);
         else
            digitalWrite( DATA_R0 + j, HIGH);                                  
      }   // for j
           
      select_line(i);                       // 選擇掃描線
      digitalWrite(EN, HIGH);               // 打開掃描線   
      
      delayMicroseconds(150);
   }   // for i
   
   count = count + 1;
   
   if(count > 300)
   {
      count = 0;
      page_num = (page_num + 1 ) % 10;    
   }     
      
}


void select_line(unsigned char number)
{
   unsigned char i;
   
   if(number == 0)
   {
      digitalWrite(S0, LOW);        
      digitalWrite(S1, LOW);        
      digitalWrite(S2, LOW);                    
   }   
   else if(number == 1)
   {
      digitalWrite(S0, HIGH);        
      digitalWrite(S1, LOW);        
      digitalWrite(S2, LOW);                    
   }   
   else if(number == 2)
   {
      digitalWrite(S0, LOW);        
      digitalWrite(S1, HIGH);        
      digitalWrite(S2, LOW);                    
   }
   else if(number == 3)
   {
      digitalWrite(S0, HIGH);        
      digitalWrite(S1, HIGH);        
      digitalWrite(S2, LOW);                    
   }
   else if(number == 4)
   {
      digitalWrite(S0, LOW);        
      digitalWrite(S1, LOW);        
      digitalWrite(S2, HIGH);                    
   }
   else if(number == 5)
   {
      digitalWrite(S0, HIGH);        
      digitalWrite(S1, LOW);        
      digitalWrite(S2, HIGH);                    
   }
   else if(number == 6)
   {
      digitalWrite(S0, LOW);        
      digitalWrite(S1, HIGH);        
      digitalWrite(S2, HIGH);                    
   }
   else if(number == 7)
   {
      digitalWrite(S0, HIGH);        
      digitalWrite(S1, HIGH);        
      digitalWrite(S2, HIGH);                    
   }                     
}


