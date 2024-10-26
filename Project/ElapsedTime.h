namespace MyApp {
class ElapsedTime {
public:
  ElapsedTime(unsigned long time_now);
  char* getTime();
private:
  unsigned long time_now;
  void convertMilliSeconds(unsigned long* day, unsigned long* hour, unsigned long* min, unsigned long* sec);
  char* getTwoDigit(unsigned long number);
};
}
