#ifndef DDECORATIONSETTINGS_H
#define DDECORATIONSETTINGS_H

#include "dsettings.h"

struct colorDecorSets
{
    QString text;
    QString link;
    QString background;
    QString linkBackground;
};

struct linksDecorSets
{
    QString social;
    QString lastfm;
    QString listen;
    QString store;
};

struct iconColorDecorSets
{
    QString main;
    QString background;
    QString border;
};

struct iconSizeDecorSets
{
    QString main;
    QString background;
    QString borderRadius;
    QString borderWidth;
};

struct iconTypeDecorSets
{
    int type;
};

struct iconShadowDecorSets
{
    int iconShadowActive;
    int iconShadowType;
};

struct iconActiveDecorSets
{
    int activeSocialIcon;
    int activeLastfmIcon;
    int activeListenIcon;
    int activeStoreIcon;
};

class dDecorationSettings : public dSettings
{
    Q_OBJECT

public:
    dDecorationSettings(dTemplate* tmplt);

private:
    colorDecorSets      colorSets;
    linksDecorSets      linksSets;
    iconColorDecorSets  iconColorSets;
    iconShadowDecorSets iconShadowSets;
    iconSizeDecorSets   iconSizeSets;
    iconActiveDecorSets iconActiveSets;
    iconTypeDecorSets   iconTypeSets;
};

#endif // DDECORATIONSETTINGS_H
