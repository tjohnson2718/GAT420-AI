#include "Node.h"

void traverse(node_t* node)
{
	node_t* nextNode = node->execute();
	if (nextNode)
	{
		traverse(nextNode);
	}
}

int main()
{
	bool isSunny = false;

// if sunny
	bool goingToBeach = true;
	// Sunny->if going to the beach
	bool haveSunscreen = true;
	// Sunny->if not going to beach
	bool isFamilyOuting = false;

// if not sunny
	bool haveOutdoorPlans = true;
	// Not Sunny->isOutdoor
	bool isWindy = false;
	// Not Sunny->notOutdoor
	bool isIndoors = true;

// Actions
	node_t* beachAction = new action_t("Going to the beach!");
	node_t* purchaseSuncreenAction = new action_t("Purchase sunscreen");
	node_t* planFamilyActivitiesAction = new action_t("Plan activities suitible for the family");
	node_t* individualActivitesAction = new action_t("Plan solo activities");
	node_t* bringJacketAction = new action_t("You should bring a jacket");
	node_t* noWindAction = new action_t("Enjoy a day with no wind");
	node_t* relaxAction = new action_t("Relax at home today");
	node_t* indoorActivitiesAction = new action_t("Plan indoor activities");

// Root
	node_t* root = new decision_t<bool>("Is it sunny?", isSunny, ePredicate::Equal, true);

// Root Decision
	node_t* beachDecision = new decision_t<bool>("are you going to the beach", goingToBeach, ePredicate::Equal, true);
	node_t* outdoorDecision = new decision_t<bool>("Do you have outdoor plans", haveOutdoorPlans, ePredicate::Equal, true);
// Beach Decisions
	// Yes Beach
	node_t* haveSunscreenDecision = new decision_t<bool>("haveSunscreen", haveSunscreen, ePredicate::Equal, true);
	// No Beach
	node_t* isFamilyDecision = new decision_t<bool>("Is it a family outing", isFamilyOuting, ePredicate::Equal, true);
// Outdoor Decisions
	// Yes Outdoors
	node_t* isWindyDecision = new decision_t<bool>("Is it windy", isWindy, ePredicate::Equal, true);
	// No Outdoors
	node_t* isStayingIndoorsDecision = new decision_t<bool>("Are you staying indoors", isIndoors, ePredicate::Equal, true);
	
// Root Decisions
	root->trueNode = beachDecision;
	root->falseNode = outdoorDecision;

	// Beach Decision
	beachDecision->trueNode = haveSunscreenDecision;
	beachDecision->falseNode = isFamilyDecision;

		// Sunscreen Decision
		haveSunscreenDecision->trueNode = beachAction;
		haveSunscreenDecision->falseNode = purchaseSuncreenAction;

		// Family Outing Decision
		isFamilyDecision->trueNode = planFamilyActivitiesAction;
		isFamilyDecision->falseNode = individualActivitesAction;

	// Outdoor Decision
	outdoorDecision->trueNode = isWindyDecision;
	outdoorDecision->falseNode = isStayingIndoorsDecision;

		// Windy Decision
		isWindyDecision->trueNode = bringJacketAction;
		isWindyDecision->falseNode = noWindAction;

		// Indoors Decision
		isStayingIndoorsDecision->trueNode = relaxAction;
		isStayingIndoorsDecision->falseNode = indoorActivitiesAction;

// traverse tree
	traverse(root);


}