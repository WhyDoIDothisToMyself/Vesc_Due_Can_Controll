void gotFrameMB0(CAN_FRAME *frame);
void gotFrameMB1(CAN_FRAME *frame);
void gotFrameMB2(CAN_FRAME *frame);
void gotFrameMB3(CAN_FRAME *frame);
void gotFrameMB6(CAN_FRAME *frame);
void gotFrame(CAN_FRAME *frame);
void printFrame(CAN_FRAME &frame);
void printFrame(CAN_FRAME *frame, int filter);
bool can_init();
