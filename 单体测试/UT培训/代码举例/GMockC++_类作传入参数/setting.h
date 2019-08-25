#ifndef _SETTING_H
#define _SETTING_H
class Setting
{
public:
virtual ~Setting(){};
public:
virtual bool get(){return false;}
int m_state;
};

#endif
