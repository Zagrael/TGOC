//
// Created by Sabrine Riahi on 2018-12-11.
//

#ifndef CHALLENGE_ANTEXCEPTION_H
#define CHALLENGE_ANTEXCEPTION_H
class antException{
public:
    enum{
        TO_DELETE,
        TO_REGISTER
    };
    int state;
    ant *a;
};
#endif //CHALLENGE_ANTEXCEPTION_H
