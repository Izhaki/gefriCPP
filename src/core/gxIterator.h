#ifndef gxIterator_h
#define gxIterator_h


/**
 * @brief A performance-opetimized iterator class warping the standard library
 * iterator.
 *
 * The class takes a container and allows iteration of its element.
 */

template < class tContainer >
class gxIterator {
protected:
    typedef typename tContainer::value_type tElement;
    typedef typename tContainer::iterator   tIterator;
public:
    gxIterator( tContainer* aContainer ):
        mContainer( aContainer )
    { }
    
    virtual void First()
    {
        mIterator = (*mContainer).begin();
        UpdateCurrent();
    }
    
    inline tElement Current()
    {
        return mCurrent;
    }
    
    virtual void Next()
    {
        ++mIterator;
        UpdateCurrent();
    }
    
    virtual int Count()
    {
        return (*mContainer).size();
    }
    
protected:
    tContainer* mContainer;
    tIterator   mIterator;
    tElement    mCurrent;
    
    void UpdateCurrent()
    {
        bool iNotLast = mIterator != (*mContainer).end();
        mCurrent = iNotLast ? *mIterator : NULL;
    }
};


#endif //gxIterator_h
