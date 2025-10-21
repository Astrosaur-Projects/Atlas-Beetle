/*
* The AtlasMenuBar has several "menus", including: AtlasMenuFile, AtlasMenuHelp, etc... Each of these menus have several options that can be selected (About, License, GitHub, etc...).
* Each option within these menus must be represented by a unique integer ID such that their events can be appropriately bound to expected behaviors.
*/
enum class AtlasMenuOptionEnums : int
{
	ID_HELLO = 10001,
	ID_GITHUB = 10002,
};