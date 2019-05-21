enum ServoState {CALLIB, IDLE, IN_PROGRESS};
enum DetectorState{ACTIVE, INACTIVE};


struct Servo
{
enum ServoState eState;
unsigned int uiCurrentPosition;
unsigned int uiDesiredPosition;
};

void DetectorInit(void);
enum DetectorState eReadDetector(void);
void ServoCallib(void);
void ServoGoTo(unsigned int uiPosition);
void Automat(void);
void ServoInit(unsigned int uiServoFrequency);
