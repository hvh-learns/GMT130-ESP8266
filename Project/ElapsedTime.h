namespace MyApp {
class ElapsedTime {
public:
  ElapsedTime(unsigned long time_now);
  void getTime(char *posOne, char *posTwo, char *posThree);
private:
  unsigned long time_now;
  void convertMilliSeconds(unsigned long* day, unsigned long* hour, unsigned long* min, unsigned long* sec);
  void getTwoDigit(unsigned long number, char *output);
};
}
