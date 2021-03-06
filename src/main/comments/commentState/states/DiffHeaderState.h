#ifndef MUSTARD_DIFFHEADERSTATE_H
#define MUSTARD_DIFFHEADERSTATE_H


#include "../CommentState.h"

class DiffHeaderState : public CommentState
{
public:
    DiffHeaderState ( CommentStateListener *commentStateListener, LineClassifier *lineClassifier = nullptr );

    shared_ptr<CommentState> traverse ( LineClassifier::LineType lineType ) override;
private:
    CommentStateListener *listener;
    LineConsumer consumer;
};


#endif //MUSTARD_DIFFHEADERSTATE_H
