
# Gameplay Ability System

```ini

; Gameplay Tags
; Debuff.TEST

; TEST GAS
[GAS]
DefaultAttributeSets = AttributeSet_Test

; AttributeSetDefine
[AttributeSet_Test]
; List of GameplayAttribute
Attributes = HP, SP, OP

; GameplayAbilityDefine
[Ability_GoodBuff]
; Name of the script that can create ability
AbilityCreator = me/GoodBuff.js
; Tags to apply to activating owner while this ability is active.
ActivationOwnedTags = Good, Good1.good

CostGameplayEffectClass = Effect_GiveSP

; GameplayEffectModifierMagnitude
[TestGEModifierMagnitude]
MagnitudeCalculationType = ScalableFloat
ScalableFloatMagnitude = 10

; GameplayEffect
[Effect_GiveSP]
DurationPolicy = HasDuration
DurationMagnitude = TestGEModifierMagnitude
Modifiers = HP:10:AddBase, SP:5:AddBase
GEComponents = TestGEComponent

; GameplayEffectComponent
[TestGEComponent]
; Type of GameplayEffectComponent
$Type = TargetTagsGEComponent
GrantedTags = TestGrantTag

[HTK]
; extra attributes
ASC.Attributes = 
; my abilities
ASC.DefaultAbilities = Ability_GoodBuff
; startup tags
ASC.StartupTags = HTKTag
; startup effects
ASC.StartupEffects = 

; TEST GAS
```
