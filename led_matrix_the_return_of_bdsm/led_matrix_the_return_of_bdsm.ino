#define MATRIX_WIDTH 7
#define MATRIX_HEIGTH 7

int led_pins[] = {7, 8, 9, 10, 11, 12, 13};
int clk = 5;
int rst = 6;

int up = 3;
int down = 4;

class Matrix{
  const int width_;
  const int heigth_;
  bool **matrix_;
public:
  Matrix(int width, int heigth): width_(width), heigth_(heigth){
    matrix_ = new bool*[heigth_];
    for(int i = 0 ; i < heigth_ ; ++ i){
      matrix_[i] = new bool[width_];
    }
  }

  ~Matrix(){
    for(int i = 0 ; i < heigth_ ; ++ i){
     delete matrix_[i];
    }
    delete matrix_;
  }

  Matrix& operator=(bool shape[7][7]){
    Serial.begin(9600);
    for(int i = 0 ; i < heigth_ ; ++ i){
      for(int j = 0 ; j < width_ ; ++ j){
        matrix_[i][j] = shape[i][j];
        Serial.print(matrix_[i][j]);
      }
      Serial.println();
    }
  }
  
  class Proxy {
    bool* array_;
  public:
    Proxy(bool* array_new) : array_(array_new) { }

    bool& operator[](bool index) {
     return array_[index];
    }
  };
    
  Proxy operator[](int index){
    return Proxy(matrix_[index]);
  }
  
};

//bool x_shape[7][7] = {{1, 0, 0, 0, 0, 0, 1},
//                      {0, 1, 0, 0, 0, 1, 0},
//                      {0, 0, 1, 0, 1, 0, 0},
//                      {0, 0, 0, 1, 0, 0, 0},
//                      {0, 0, 1, 0, 1, 0, 0},
//                      {0, 1, 0, 0, 0, 1, 0},
//                      {1, 0, 0, 0, 0, 0, 1}};
//                      
//bool swastika[7][7] = {{1, 0, 0, 1, 1, 1, 1},
//                       {1, 0, 0, 1, 0, 0, 0},
//                       {1, 0, 0, 1, 0, 0, 0},
//                       {1, 1, 1, 1, 1, 1, 1},
//                       {0, 0, 0, 1, 0, 0, 1},
//                       {0, 0, 0, 1, 0, 0, 1},
//                       {1, 1, 1, 1, 0, 0, 1}};
//
//bool kawaii_shape[7][7] = {{0, 0, 0, 1, 0, 0, 0},
//                           {0, 0, 1, 0, 1, 0, 0},
//                           {0, 1, 0, 0, 0, 1, 0},
//                           {1, 0, 0, 0, 0, 0, 1},
//                           {0, 0, 0, 0, 0, 0, 0},
//                           {0, 0, 0, 0, 0, 0, 0},
//                           {0, 0, 0, 0, 0, 0, 0}};

bool x_shape[7][7] = {{0, 0, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 0, 0, 0},
                      {0, 0, 0, 0, 1, 1, 0},
                      {0, 1, 1, 0, 1, 1, 0},
                      {0, 0, 0, 0, 0, 0, 0},
                      {0, 1, 0, 0, 0, 1, 0},
                      {0, 0, 1, 1, 1, 0, 0}};
                      
bool swastika[7][7] = {{0, 1, 1, 0, 0, 0, 0},
                       {0, 0, 0, 0, 0, 0, 0},
                       {0, 1, 1, 0, 1, 1, 0},
                       {0, 1, 1, 0, 1, 1, 0},
                       {0, 0, 0, 0, 0, 0, 0},
                       {0, 1, 0, 0, 0, 1, 0},
                       {0, 0, 1, 1, 1, 0, 0}};

bool kawaii_shape[7][7] = {{0, 0, 0, 0, 0, 0, 0},
                           {0, 0, 0, 0, 0, 0, 0},
                           {0, 1, 1, 0, 1, 1, 0},
                           {0, 1, 1, 0, 1, 1, 0},
                           {0, 0, 0, 0, 0, 0, 0},
                           {0, 1, 0, 0, 0, 1, 0},
                           {0, 0, 1, 1, 1, 0, 0}};

Matrix matrix(MATRIX_WIDTH, MATRIX_HEIGTH);

void setup() {
  // put your setup code here, to run once:
  for(int i = 0 ; i < MATRIX_WIDTH ; ++ i){
    pinMode(led_pins[i], OUTPUT);
  }
  for(int i = 0 ; i < MATRIX_WIDTH ; ++ i){
    digitalWrite(led_pins[i], HIGH);
  }
  
  pinMode(clk, OUTPUT);
  digitalWrite(clk, LOW);
  pinMode(rst, OUTPUT);
  digitalWrite(rst, LOW);

  pinMode(up, INPUT_PULLUP);
  pinMode(down, INPUT_PULLUP);
  
  matrix = swastika;
}

void loop() {

//  for(int i = 0 ; i < MATRIX_HEIGTH ; ++ i){
//
//    for(int j = 0 ; j < MATRIX_WIDTH ; ++ j){
//      digitalWrite(led_pins[j], LOW);
//      delay(100);
//      digitalWrite(led_pins[j], HIGH);
//    }
//    digitalWrite(clk, HIGH);
//    digitalWrite(clk, LOW);
//  }
//  digitalWrite(rst, HIGH);
//  digitalWrite(rst, LOW);
  //delay(5000);

  if(digitalRead(up) == LOW){
   
    for(int i = 0 ; i < MATRIX_HEIGTH ; ++ i){

      for(int j = 0 ; j < MATRIX_WIDTH ; ++ j){
        if(x_shape[i][j] == true){
          digitalWrite(led_pins[j], LOW);
          delay(1);
          digitalWrite(led_pins[j], HIGH);
        }
      }
      digitalWrite(clk, HIGH);
      digitalWrite(clk, LOW);
    }
    digitalWrite(rst, HIGH);
    digitalWrite(rst, LOW);
  }else if(digitalRead(down) == LOW){

    for(int i = 0 ; i < MATRIX_HEIGTH ; ++ i){

      for(int j = 0 ; j < MATRIX_WIDTH ; ++ j){
        if(swastika[i][j] == true){
          digitalWrite(led_pins[j], LOW);
          delay(1);
          digitalWrite(led_pins[j], HIGH);
        }
      }
      digitalWrite(clk, HIGH);
      digitalWrite(clk, LOW);
    }
    digitalWrite(rst, HIGH);
    digitalWrite(rst, LOW);
  }else{
    for(int i = 0 ; i < MATRIX_HEIGTH ; ++ i){

      for(int j = 0 ; j < MATRIX_WIDTH ; ++ j){
        if(kawaii_shape[i][j] == true){
          digitalWrite(led_pins[j], LOW);
          delay(1);
          digitalWrite(led_pins[j], HIGH);
        }
      }
      digitalWrite(clk, HIGH);
      digitalWrite(clk, LOW);
    }
    digitalWrite(rst, HIGH);
    digitalWrite(rst, LOW);
  }
}

