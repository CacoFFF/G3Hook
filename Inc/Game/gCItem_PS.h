#pragma once

//G3Hook stuff
struct ReqAttrib
{
	bCString Tag;
	bTPropertyContainer<EAttribReqOperation> Op;
	int Value;
};

class G3GAMEAPI gCItem_PS : public eCEntityPropertySet
{
public:
	PS_EPROPERTY(Amount,uint32);                      // 0x14
	PS_EPROPERTY(Quality,uint32);                     // 0x18
	PS_EPROPERTY(GoldValue,int32);                    // 0x1C
	PS_EPROPERTY(MissionItem,bool);                   // 0x20
	PS_EPROPERTY(Permanent,bool);                     // 0x21
	PS_EPROPERTY(Category,bTPropertyContainer<gEItemCategory>); // 0x24
	PS_EPROPERTY(Texture,bCString);                   // 0x2C
	PS_EPROPERTY(Dropped,bool);                       // 0x30
	PS_EPROPERTY(ItemWorld,eCTemplateEntityProxy);    // 0x34
	PS_EPROPERTY(ItemInventory,eCTemplateEntityProxy);// 0x40
	PS_EPROPERTY(ArmorSet,eCTemplateEntityProxy);     // 0x4C
	PS_EPROPERTY(Spell,eCTemplateEntityProxy);        // 0x58
	PS_EPROPERTY(Skill,eCTemplateEntityProxy);        // 0x64
	PS_EPROPERTY(Robe,bool);                          // 0x70
	PS_EPROPERTY(FullBody,bool);                      // 0x71
	PS_EPROPERTY(ReqAttrib1Tag,bCString);             // 0x74
	PS_EPROPERTY(ReqAttrib1Op,bTPropertyContainer<EAttribReqOperation>); // 0x78
	PS_EPROPERTY(ReqAttrib1Value,int);                // 0x80
	PS_EPROPERTY(ReqAttrib2Tag,bCString);             // 0x84
	PS_EPROPERTY(ReqAttrib2Op,bTPropertyContainer<EAttribReqOperation>); // 0x88
	PS_EPROPERTY(ReqAttrib2Value,int);                // 0x90
	PS_EPROPERTY(ReqAttrib3Tag,bCString);             // 0x94
	PS_EPROPERTY(ReqAttrib3Op,bTPropertyContainer<EAttribReqOperation>); // 0x98
	PS_EPROPERTY(ReqAttrib3Value,int);                // 0xA0
	PS_EPROPERTY(ReqAttrib4Tag,bCString);             // 0xA4
	PS_EPROPERTY(ReqAttrib4Op,bTPropertyContainer<EAttribReqOperation>); // 0xA8
	PS_EPROPERTY(ReqAttrib4Value,int);                // 0xB0
	PS_EPROPERTY(RequiredSkill1,eCTemplateEntityProxy);// 0xB4
	PS_EPROPERTY(RequiredSkill2,eCTemplateEntityProxy);// 0xC0
	//More props missing!

	bool IsEquipped() const;
	bool ExecuteScript() const;
	int Compare( const gCItem_PS&, const gCInventory_PS&) const;
	int GetModValue( const bCString&) const;
};
