#ifndef SPATIAL_ENTITY_H
#define SPATIAL_ENTITY_H

#include <math.hpp>
#include <id_manager.hpp>
#include <string>

namespace MFGame
{

/**
  Abstract interface for something that exists in 3D world and has a graphical and/or
  physical and/or sound etc. representations.
 */

class SpatialEntity
{
public:
    SpatialEntity();
    virtual ~SpatialEntity();

    virtual void update(double dt)=0;

    /**
      Initialises the entity with currently set data (OSG node, Bullet body, ...) so that it
      is ready to work.
    */
    virtual void ready()=0;
    virtual std::string toString()                      { return "";            };
    MFMath::Vec3 getPosition()                          { return mPosition;     };
    virtual void setPosition(MFMath::Vec3 position)     { mPosition = position; };   ///< Sets position without collisions.
    virtual void setVelocity(MFMath::Vec3 velocity)=0;
    virtual void setAngularVelocity(MFMath::Vec3 velocity)=0;
    MFMath::Quat getRotation()                          { return mRotation;     };
    virtual void setRotation(MFMath::Quat rotation)     { mRotation = rotation; };
    virtual bool hasVisual()=0;
    virtual bool canBeMoved()=0;                        ///< Says whether the entity can be transformed with setPosition(...) etc.
//  detach()
//  mergeWithChildren()

    virtual bool hasCollision()=0;
    void setName(std::string name)                      { mName = name;         };
    std::string getName()                               { return mName;         };
    bool isRead()                                       { return mReady;        };
    Id getId()                                          { return mId;           };
    
    /**
    Moves the entity from current to dest position, checking for collisions.
    */
    virtual void move(MFMath::Vec3 destPosition)=0;

    static void setIDManager(std::shared_ptr<IDManager> manager) { sIDManager = manager; }
    static IDManager *getIDManager() 
    { 
        if (sIDManager.get() == nullptr)
            sIDManager = std::make_shared<BackingIDManager>();

        return sIDManager.get(); 
    }

  protected:
    MFMath::Vec3 mPosition;
    MFMath::Vec3 mScale;
    MFMath::Quat mRotation;

    std::string mName;
    bool mReady;
    Id mId;
    static std::shared_ptr<IDManager> sIDManager;
};

SpatialEntity::SpatialEntity()
{
    mId = getIDManager()->allocate();
    mPosition = MFMath::Vec3();
    mScale = MFMath::Vec3(1,1,1);
    mReady = true;
}

SpatialEntity::~SpatialEntity()
{
    getIDManager()->deallocate(mId);
}

std::shared_ptr<IDManager> SpatialEntity::sIDManager;

}
#endif
