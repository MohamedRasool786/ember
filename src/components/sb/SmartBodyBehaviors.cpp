#include "SmartBodyBehaviors.h"
#include "SmartBodyRetarget.h"
#include "SmartBodyManager.h"

#include "sb/SBAssetManager.h"
#include "sb/SBCharacter.h"
#include "sb/SBSkeleton.h"
#include "sb/SBScene.h"



using namespace Ember;
namespace Ember
{

SmartBodyBehaviors::SmartBodyBehaviors(const std::string& motionPath, const std::string& skeletonRef, SmartBodyManager& manager)
	: mSkelRefName(skeletonRef), mSetup(false), mAssetManager(manager.getAssetManager()), mBlendManager(*manager.getScene().getBlendManager()),
	  mRetargetManager(*manager.getScene().getRetargetManager())
{
	//Loads the assets.
	mAssetManager.loadAssetsFromPath(motionPath);
}

SmartBodyBehaviors::~SmartBodyBehaviors()
{

}


bool SmartBodyBehaviors::setup(bool check)
{
	//If setup has alredy been called, do nothing.
	if (!mSetup)
	{
		//Before setting up the behaviors, checks their existence. 
		if (!check || assetsExist())
		{		
			setupBehaviors();
			mSetup = true;
		}
	}

	return mSetup;
}

bool SmartBodyBehaviors::assetsExist(void)
{
	if (!mAssetManager.getSkeleton(mSkelRefName))
	{
		//std::cout << "Error : " + mSkelRefName + " does not exists." << std::endl;
		return false;
	}

	std::vector<std::string> motions = getMotions();
	for (int i = 0; i < motions.size(); i ++)
	{
		SmartBody::SBMotion *motion = mAssetManager.getMotion(motions[i]);

		if (!motion)
		{
			//std::cout << "Error : " + motions[i] + " does not exists." << std::endl;
			return false;
		}
	}

	return true;		
}

void SmartBodyBehaviors::setupBehaviors(void)
{
	//We get the motion paths for this behavior set. 
	std::vector<std::string> motions = getMotions();

	//For each motion, we need to set the skeleton and to configurate some of the motion parameters. 
	int size = motions.size();
	for (int i = 0; i < size; i ++)
	{
		SmartBody::SBMotion *motion = mAssetManager.getMotion(motions[i]);
		motion->setMotionSkeletonName(mSkelRefName);
		setupMotion(*motion);
	}		
}


void SmartBodyBehaviors::retarget(SmartBody::SBCharacter& character)
{
	//Cannot retarget if setup has not been called previously.
	assert(mSetup);

	std::string skelName = character.getSkeleton()->getName();

	//Creation of the retargeting object.
	SmartBodyRetarget retarget(mSkelRefName, skelName, mRetargetManager);
}

}