
#ifndef STATUSDISPLAY_H_
#define STATUSDISPLAY_H_


class StatusDisplay {
public:
	StatusDisplay();
	virtual ~StatusDisplay();

	void showMode(int mode);
	void showActive(bool b);
};

#endif /* STATUSDISPLAY_H_ */
