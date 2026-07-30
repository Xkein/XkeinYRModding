# Gameplay Ability System (GAS) 框架文档

## 目录

1. [架构概览](#1-架构概览)
2. [GameplayTag（游戏标签）](#2-gameplaytag游戏标签)
3. [AttributeSet（属性集）](#3-attributeset属性集)
4. [GameplayAbility（游戏能力）](#4-gameplayability游戏能力)
5. [GameplayEffect（游戏效果）](#5-gameplayeffect游戏效果)
6. [GEComponent（效果组件）](#6-gecomponent效果组件)
7. [AbilityTask（能力任务）](#7-abilitytask能力任务)
8. [AbilitySystemComponent（ASC）](#8-abilitysystemcomponentasc)
9. [GameplayCue（游戏提示）](#9-gameplaycue游戏提示)
10. [属性聚合系统](#10-属性聚合系统)
11. [SetByCaller](#11-setbycaller)
12. [CurveTable（曲线表）](#12-curvetable曲线表)
13. [INI 配置完整参考](#13-ini-配置完整参考)
14. [快速开始](#14-快速开始)
15. [已知限制](#15-已知限制)
16. [委托存档（Delegate Savegame）](#16-委托存档delegate-savegame)
17. [嵌套结构体 INI 加载](#17-嵌套结构体-ini-加载)

---

## 1. 架构概览

```
AbilitySystemGlobals ([GAS])
         |
         | 管理全局配置、曲线表、工厂函数
         v
AbilitySystemComponent (ASC)  [TechnoType] ASC.*
   /        |        \
  v         v         v
Attribute  Ability   ActiveGameplay
  Set       Spec      Effects Container
   |         |           |
   v         v           v
Gameplay   Gameplay    GameplayEffect
Attribute  Ability     (Instant/Infinite/
  Data     (激活、     HasDuration)
  (Base/   提交、            |
  Current) 结束)        GEComponents
                        (11种子类型)
                           |
                           v
                      FAggregator
                      (属性聚合器)
```

**核心流程：**

1. AbilitySystemGlobals 加载全局 `[GAS]` 配置和 `[CurveTable.*]` 曲线表
2. 单位创建时，AbilitySystemComponent 从 `[TechnoType]` 读取 `ASC.*` 配置
3. ASC 初始化 AttributeSet、赋予默认 Ability、应用启动时 GE
4. Ability 被激活后，创建 AbilityTask 执行具体逻辑
5. Ability 提交时应用 Cost GE 和 Cooldown GE
6. GE 修改属性时经过 Aggregator（聚合器）计算最终值
7. GE 可以带 GEComponent 实现标签授予、免疫、额外效果等行为

---

## 2. GameplayTag（游戏标签）

### 2.1 基本概念

GameplayTag（游戏标签）是一个以点分隔的层次化标签系统，用于标记和查询游戏对象的状态。标签格式如 `"Debuff.Fire.Stun"`，支持父子层级匹配。

### 2.2 标签层级与父级匹配

```ini
; 标签示例
Debuff.Fire.Stun
Debuff.Fire.Burn
Debuff.Poison
Buff.Speed
Buff.Strength
Ability.SpecialAttack
```

匹配规则：

- `"A.1".MatchesTag("A")` 返回 true（父级匹配）
- `"A".MatchesTag("A.1")` 返回 false（子级不匹配父级）
- `"A.1".MatchesTag("A.1")` 返回 true（精确匹配）
- `"Debuff.Fire.Stun".MatchesTag("Debuff")` 返回 true

### 2.3 GameplayTagContainer（标签容器）

容器可以持有多个标签，提供集合查询：

```typescript
// TypeScript API
const tag = new GameplayTag();
tag.m_TagName = "Debuff.Fire";

const container = new GameplayTagContainer();
container.m_GameplayTags.Add(tag);

// 查询
container.HasTag(tag);          // true, 支持父级匹配
container.HasTagExact(tag);     // true, 精确匹配
container.HasAll(otherContainer);
container.HasAny(otherContainer);
```

### 2.4 GameplayTagQuery（标签查询表达式）

支持 AND/OR/NOT 组合的表达式树查询：

```typescript
// 构建查询
const query = GameplayTagQuery.MakeQuery_MatchAnyTagsMatch(container);
const allQuery = GameplayTagQuery.MakeQuery_MatchAllTagsMatch(container);

// 执行查询
query.Matches(someContainer);
```

表达式节点类型：`AnyTagsMatch`、`AllTagsMatch`、`NoTagsMatch`、`AnyExprMatch`、`AllExprMatch`、`NoExprMatch`

### 2.5 GameplayTagRequirements（标签需求）

封装 RequireTags（必须含有）、IgnoreTags（不能含有）和 TagQuery（表达式树查询）：

```ini
; INI 配置 — 用于 Ability 和 GE 的标签检查
[Ability_Test]
ActivationRequiredTags = Buff.Speed
ActivationBlockedTags = Debuff.Stun
SourceRequiredTags = Player.Ally
SourceBlockedTags = Player.Enemy
TargetRequiredTags = Enemy
TargetBlockedTags = Ally.Invincible
```

```typescript
// TypeScript API
const req = new GameplayTagRequirements();
req.m_RequireTags = tagContainer;
req.m_IgnoreTags = otherContainer;
req.m_TagQuery = GameplayTagQuery.MakeQuery_MatchAnyTagsMatch(container);

req.RequirementsMet(someContainer);  // true/false
```

### 2.6 标签改变事件（FOnGameplayTagCountChanged）

当 ASC 上的标签计数变化时通过委托广播：

```typescript
// TypeScript: 注册标签计数变化回调
asc.RegisterGameplayTagEvent(tag);  // 返回 FOnGameplayTagCountChanged
```

### 2.7 FInheritedTagContainer（可继承标签容器）

支持父子继承的标签容器，计算公式：`Combined = Inherited - Removed + Added`

嵌套结构体支持两种 INI 配置方式（详见 [第 17 节](#17-嵌套结构体-ini-加载)）：

```ini
; 方式1：点分键展开（在当前 section 下用 属性名.子字段 读取）
[Comp_BlockAbility]
InheritableBlockedAbilityTagsContainer.Added = Ability.Attack
InheritableBlockedAbilityTagsContainer.Removed = Ability.Safe

; 方式2：section 引用（属性值作为 section 名，去该节下读取子字段）
[Comp_BlockAbility]
InheritableBlockedAbilityTagsContainer = MyBlockedTags

[MyBlockedTags]
Added = Ability.Attack
Removed = Ability.Safe
```

---

## 3. AttributeSet（属性集）

### 3.1 概念

AttributeSet（属性集）是属性的集合，负责存储和修改游戏属性（例如生命值、魔法值、攻击力）。

三层定义：

| 层级 | 类名 | 用途 |
|---|---|---|
| 定义层 | AttributeSetDefine | INI 配置定义，声明属性列表和创建器 |
| 基类层 | AttributeSet | C++ 基类，提供属性存储和生命周期钩子 |
| 脚本层 | CustomAttributeSet | TypeScript 可重写的属性集，暴露所有回调 |

### 3.2 GameplayAttributeData（属性数据）

每个属性包含两个值：

```cpp
struct GameplayAttributeData {
    float BaseValue;      // 基础值（永久修改）
    float CurrentValue;   // 当前值（包含临时修改）
};
```

- `GetBaseValue()` / `SetBaseValue()` — 永久值操作
- `GetCurrentValue()` / `SetCurrentValue()` — 当前值操作

### 3.3 AttributeSetDefine（INI 定义）

```ini
[AttributeSet_Test]
; AttributeSetCreator = 脚本路径，用于创建自定义属性集
AttributeSetCreator = xkein/gas/test_attribute_set

; Attributes = 逗号分隔的属性名列表
; 格式: AttrName1, AttrName2, ...
; 注意：属性名前自动加上 Section 名为 owner
Attributes = HP, SP, OP
```

### 3.4 ATTRIBUTE_ACCESSORS 宏

```cpp
// 在自定义 AttributeSet 中声明属性访问器
ATTRIBUTE_ACCESSORS(MyAttributeSet, Health);
// 展开为：
//   static GameplayAttribute GetHealthAttribute()
//   float GetHealth() const
//   void SetHealth(float NewVal)
//   void InitHealth(float NewVal)
```

### 3.5 CustomAttributeSet 脚本回调

```typescript
// TypeScript
const set = CustomAttributeSet.Create();

// 所有回调均为 PROPERTY TDelegate，通过 BindStdFunction 绑定 JS lambda（不可存档）
// 如需存档兼容，请使用 BindScriptFunction(category, name)，详见第 16 节
set.m_OnK2_PreGameplayEffectExecute.BindStdFunction((data: FGameplayEffectModCallbackData): boolean => {
    // GE 执行前调用。返回 false 跳过修改。
    return true;
});

set.m_OnK2_PostGameplayEffectExecute.BindStdFunction((data: FGameplayEffectModCallbackData) => {
    // GE 成功执行后调用
});

set.m_OnK2_PreAttributeChange.BindStdFunction((attr: GameplayAttribute, newValue: float) => {
    // 属性值修改前调用。newValue 可修改（用于钳制）
});

set.m_OnK2_PostAttributeChange.BindStdFunction((attr: GameplayAttribute, oldValue: float, newValue: float) => {
    // 属性值修改后调用
});

set.m_OnK2_PreAttributeBaseChange.BindStdFunction((attr: GameplayAttribute, newValue: float) => {
    // 基础值修改前调用
});

set.m_OnK2_PostAttributeBaseChange.BindStdFunction((attr: GameplayAttribute, oldValue: float, newValue: float) => {
    // 基础值修改后调用
});
```

回调表格：

| 回调名称 | 时机 | 可阻断 |
|---|---|---|
| OnK2_PreGameplayEffectExecute | GE 执行修改前 | 是（返回 false） |
| OnK2_PostGameplayEffectExecute | GE 修改成功后 | 否 |
| OnK2_PreAttributeChange | 属性值改变前 | 否（可钳制 NewValue） |
| OnK2_PostAttributeChange | 属性值改变后 | 否 |
| OnK2_PreAttributeBaseChange | 基础值改变前 | 否（可钳制 NewValue） |
| OnK2_PostAttributeBaseChange | 基础值改变后 | 否 |

### 3.6 脚本层工厂注册

```typescript
// test_attribute_set.ts
export function attribute_set_creator(define: AttributeSetDefine, com: AbilitySystemComponent): AttributeSet {
    const set = CustomAttributeSet.Create();
    // 设置初始值
    // 绑定回调
    return set;
}
```

---

## 4. GameplayAbility（游戏能力）

### 4.1 概念

GameplayAbility（游戏能力）是可以被激活的游戏逻辑单元，包含从激活到结束的完整生命周期。

### 4.2 GameplayAbilityDefine（INI 定义字段表）

`GameplayAbilityDefine` 标记为 `IniAutoLoad`，每个 `[Ability_XXX]` section 自动创建一个实例。各字段通过 `Parser<T>` 特化或 `IniComponentLoader` 递归加载，不同类型的 INI 写法不同：

| 字段 | 类型 | INI 写法 | 说明 |
|---|---|---|---|
| AbilityCreator | StringName | 脚本路径字符串 | 脚本创建器路径 |
| AbilityTags | GameplayTagContainer | 逗号分隔标签 | 能力的标签（用于分类和查询） |
| InstancingPolicy | EGameplayAbilityInstancingPolicy | 枚举名 | 实例化策略 |
| bRetriggerInstancedAbility | bool | yes/no | 是否允许重复触发 |
| CostGameplayEffectClass | GameplayEffect* | GE section 名 | 消耗（法力/体力） |
| CooldownGameplayEffectClass | GameplayEffect* | GE section 名 | 冷却 |
| AbilityTriggers | vector\<AbilityTriggerData\> | 逗号分隔的 `Tag:Source` | 触发器列表（见 4.5 节） |
| CancelAbilitiesWithTag | GameplayTagContainer | 逗号分隔标签 | 激活时取消带这些标签的能力 |
| BlockAbilitiesWithTag | GameplayTagContainer | 逗号分隔标签 | 激活时阻止带这些标签的能力 |
| ActivationOwnedTags | GameplayTagContainer | 逗号分隔标签 | 激活时授予自身的标签 |
| ActivationRequiredTags | GameplayTagContainer | 逗号分隔标签 | 激活者必须含有的标签 |
| ActivationBlockedTags | GameplayTagContainer | 逗号分隔标签 | 激活者不能含有的标签 |
| SourceRequiredTags | GameplayTagContainer | 逗号分隔标签 | 来源必须含有的标签 |
| SourceBlockedTags | GameplayTagContainer | 逗号分隔标签 | 来源不能含有的标签 |
| TargetRequiredTags | GameplayTagContainer | 逗号分隔标签 | 目标必须含有的标签 |
| TargetBlockedTags | GameplayTagContainer | 逗号分隔标签 | 目标不能含有的标签 |

各类型的加载机制说明：

- **StringName**：通过 `Parser<StringName>` 直接读取字符串值
- **GameplayTagContainer**：通过 `Parser<GameplayTagContainer>`（定义于 `ability_system_globals.h`）按逗号分割，逐个解析为 `GameplayTag`
- **EGameplayAbilityInstancingPolicy**：通过泛型 `Parser<T, is_enum>` 自动解析枚举名（如 `NonInstanced`、`InstancedPerActor`、`InstancedPerExecution`）
- **bool**：通过 `Parser<bool>` 解析（`yes`/`no`/`true`/`false`）
- **GameplayEffect\***：通过泛型 `Parser<T*>` 解析，INI 值为 GE 的 section 名，内部调用 `IniAutoLoad` 注册的 `__FindOrAllocate` 元函数查找或创建 `GameplayEffect` 实例
- **vector\<AbilityTriggerData\>**：通过 `Parser<std::vector<T>>` 按逗号分割，每个元素由 `Parser<AbilityTriggerData>`（定义于 `ability_system_globals.h`）按 `Tag:Source` 格式解析，Source 可省略（默认 `GameplayEvent`）

### 4.3 实例化策略

| 策略 | 说明 | 适用场景 |
|---|---|---|
| NonInstanced | 不实例化，操作 CDO。无状态，无 ActiveTasks | 纯数学计算、查询类 |
| InstancedPerActor | 每 Actor 一个实例。共享状态 | 大部分常规能力 |
| InstancedPerExecution | 每次激活新实例。有独立状态 | 多段式、超时复杂能力 |

### 4.4 CustomGameplayAbility 脚本回调

```typescript
// TypeScript
const ability = CustomGameplayAbility.Create();

// 回调（PROPERTY TDelegate，通过 BindStdFunction 绑定 JS lambda，不可存档）
// 如需存档兼容，请使用 BindScriptFunction(category, name)，详见第 16 节
ability.m_OnK2CanActivateAbility.BindStdFunction((actorInfo, handle, tags): boolean => {
    return true; // 返回 false 阻止激活
});

ability.m_OnK2ActivateAbility.BindStdFunction(() => {
    // 能力激活时调用
});

ability.m_OnK2ActivateAbilityFromEvent.BindStdFunction((eventData: GameplayEventData) => {
    // 从事件触发时调用（优先于 OnK2ActivateAbility）
});

ability.m_OnK2CommitExecute.BindStdFunction(() => {
    // 能力提交后调用（消耗/冷却已应用）
});

ability.m_OnK2OnEndAbility.BindStdFunction((wasCancelled: boolean) => {
    // 能力结束时调用
});

// 可调用的 FUNCTION 方法
ability.K2_EndAbility();
ability.K2_CancelAbility();
ability.K2_CommitAbility();         // 提交消耗+冷却
ability.K2_CommitAbilityCooldown(); // 只提交冷却
ability.K2_CommitAbilityCost();     // 只提交消耗
ability.K2_CheckAbilityCooldown();
ability.K2_CheckAbilityCost();
ability.K2_EndAbilityLocally();
```

### 4.5 AbilityTriggerData（触发器）

`AbilityTriggerData` 是一个包含两个字段的结构体：

| 成员 | 类型 | 说明 |
|---|---|---|
| TriggerTag | GameplayTag | 响应的标签 |
| TriggerSource | EGameplayAbilityTriggerSource | 触发源类型 |

触发源枚举值：

| 触发源 | 说明 |
|---|---|
| GameplayEvent | 收到 GameplayEvent 时触发，带事件载荷 |
| OwnedTagAdded | 所有者获得指定标签时触发一次 |
| OwnedTagPresent | 所有者有指定标签时激活，移除标签时结束 |

INI 格式为 `TriggerTag:TriggerSource`，多个触发器用逗号分隔。`TriggerSource` 可省略，省略时默认为 `GameplayEvent`。

```ini
[Ability_Test]
; 完整格式：Tag:Source
AbilityTriggers = Event.Fireball:GameplayEvent, Buff.Rage:OwnedTagAdded

; 省略 Source（默认 GameplayEvent）
AbilityTriggers = Event.Fireball
```

### 4.6 激活流程

```
CallActivateAbility
  └─ PreActivate
       ├─ 创建 AbilityTasks
       ├─ 设置 CurrentActorInfo/Handle
       ├─ 应用 ActivationOwnedTags
       └─ 调用 ActivateAbility
            └─ K2_OnActivateAbility / K2_OnActivateAbilityFromEvent
```

### 4.7 提交流程

```
K2_CommitAbility
  ├─ CheckCost → ApplyCost
  ├─ CheckCooldown → ApplyCooldown
  └─ K2_OnCommitExecute
```

---

## 5. GameplayEffect（游戏效果）

### 5.1 概念

GameplayEffect（游戏效果，简称 GE）是一个数据驱动的描述符，定义如何修改属性或授予状态。它是 GAS 中修改游戏状态的核心手段。

### 5.2 持续时间策略

| 策略 | 常量值 | 说明 |
|---|---|---|
| Instant | 0.0f | 瞬时执行，立即应用修改，无持续效果 |
| Infinite | -1.0f | 永久持续，直到被移除 |
| HasDuration | > 0 | 指定持续时间，到期自动移除 |

```ini
[Effect_Heal]
DurationPolicy = Instant
Modifiers = Mod_HealHP

[Mod_HealHP]
Attribute = AttributeSet_Test.Health
ModifierOp = AddBase
ModifierMagnitude.MagnitudeCalculationType = ScalableFloat
ModifierMagnitude.ScalableFloatMagnitude = 50.0

[Effect_Buff]
DurationPolicy = HasDuration
DurationMagnitude.MagnitudeCalculationType = ScalableFloat
DurationMagnitude.ScalableFloatMagnitude = 10.0
Modifiers = Mod_BuffAttack

[Mod_BuffAttack]
Attribute = AttributeSet_Test.Attack
ModifierOp = MultiplyAdditive
ModifierMagnitude.MagnitudeCalculationType = ScalableFloat
ModifierMagnitude.ScalableFloatMagnitude = 1.5

[Effect_Poison]
DurationPolicy = Infinite
Period = 2.0
bExecutePeriodicEffectOnApplication = true
Modifiers = Mod_PoisonDmg

[Mod_PoisonDmg]
Attribute = AttributeSet_Test.Health
ModifierOp = AddBase
ModifierMagnitude.MagnitudeCalculationType = ScalableFloat
ModifierMagnitude.ScalableFloatMagnitude = -5.0
```

### 5.3 修改器（Modifier）

`Modifiers` 字段类型为 `std::vector<GameplayModifierInfo*>`（指针数组）。`GameplayModifierInfo` 标记为 `IniComponent, IniAutoLoad`，每个 Modifier 是一个独立的 INI section，通过 section 名引用：

```ini
[Effect_Heal]
; 多个 Modifier 用逗号分隔，每个值是一个 section 名
Modifiers = Mod_HealHP, Mod_HealMP

[Mod_HealHP]
; Attribute 格式: OwnerName.AttributeName
Attribute = AttributeSet_Test.Health
ModifierOp = AddBase
; ModifierMagnitude 是嵌套 IniComponent，用点分键配置（详见 5.9 节）
ModifierMagnitude.MagnitudeCalculationType = ScalableFloat
ModifierMagnitude.ScalableFloatMagnitude = 50.0

; 可选：来源/目标标签需求（GameplayTagRequirements，支持点分键或 section 引用）
; SourceTags.RequireTags = Alive
; TargetTags.IgnoreTags = Invincible
```

> **注意：** `Modifiers` 是指针数组，通过 section 名引用 `[Mod_XXX]` 节。`Parser<GameplayModifierInfo>`（非指针）虽然存在 `"Attr:Mag:Op"` 组合格式解析，但仅用于值类型场景，不适用于 `Modifiers` 字段的指针数组加载。

### 5.4 ModOp 类型与计算公式

| ModOp | 枚举值 | INI 名称 | 作用 |
|---|---|---|---|
| AddBase | 0 | AddBase / Additive | 累加到基础值 |
| MultiplyAdditive | 1 | MultiplyAdditive / Multiplicitive | 乘算（相加后乘） |
| DivideAdditive | 2 | DivideAdditive / Division | 除算（相加后除） |
| Override | 3 | Override | 覆盖最终值 |
| MultiplyCompound | 4 | MultiplyCompound | 复合乘算（相乘） |
| AddFinal | 5 | AddFinal | 最终加法 |

**完整计算公式：**

```
((BaseValue + Sum_AddBase)
    × (1 + Sum_MultiplyAdditive)
    ÷ (1 + Sum_DivideAdditive)
    × Product_MultiplyCompound)
    + Sum_AddFinal
```

**特殊情况：** 如果有 Override 类型的 Modifier，则直接返回 Override 值，忽略其他所有计算。

### 5.5 堆叠（Stacking）

| 字段 | 类型 | 说明 |
|---|---|---|
| StackingType | None/AggregateBySource/AggregateByTarget | 堆叠方式 |
| StackLimitCount | int32 | 最大堆叠层数 |
| StackDurationRefreshPolicy | RefreshOnSuccessfulApplication / NeverRefresh / ExtendDuration | 堆叠时持续时间的处理 |
| StackPeriodResetPolicy | ResetOnSuccessfulApplication / NeverReset | 堆叠时周期重置 |
| StackExpirationPolicy | ClearEntireStack / RemoveSingleStackAndRefreshDuration / RefreshDuration | 过期策略 |
| bDenyOverflowApplication | bool | 超过上限时拒绝应用 |
| bClearStackOnOverflow | bool | 超过上限时清除全部 |
| bFactorInStackCount | bool | 修改器数值是否乘以层数 |
| OverflowEffects | vector\<GameplayEffect*\> | 溢出时触发效果 |

```ini
[Effect_PoisonStack]
StackingType = AggregateBySource
StackLimitCount = 5
StackDurationRefreshPolicy = RefreshOnSuccessfulApplication
StackExpirationPolicy = ClearEntireStack
bFactorInStackCount = true
Modifiers = Mod_PoisonDmg

[Mod_PoisonDmg]
Attribute = AttributeSet_Test.Health
ModifierOp = AddBase
ModifierMagnitude.MagnitudeCalculationType = ScalableFloat
ModifierMagnitude.ScalableFloatMagnitude = -3.0
```

### 5.6 周期效果（Periodic Effect）

```ini
[Effect_Burn]
DurationPolicy = HasDuration
DurationMagnitude.MagnitudeCalculationType = ScalableFloat
DurationMagnitude.ScalableFloatMagnitude = 10.0
Period = 1.0                     ; 每秒执行一次
bExecutePeriodicEffectOnApplication = true  ; 立即执行第一次
PeriodicInhibitionPolicy = ResetPeriod
Modifiers = Mod_BurnDmg

[Mod_BurnDmg]
Attribute = AttributeSet_Test.Health
ModifierOp = AddBase
ModifierMagnitude.MagnitudeCalculationType = ScalableFloat
ModifierMagnitude.ScalableFloatMagnitude = -5.0
```

字段说明：

| 字段 | 说明 |
|---|---|
| Period | FScalableFloat，周期时间（秒） |
| bExecutePeriodicEffectOnApplication | 是否在应用时立即执行第一次 |
| PeriodicInhibitionPolicy | 抑制恢复后周期策略（NeverReset / ResetPeriod / ExecuteAndResetPeriod） |

### 5.7 等级缩放（ScalableFloat）

`FScalableFloat` 在 INI 中只能读取一个裸 float 值（通过 `Parser<FScalableFloat>`）：

```ini
Period = 2.0
```

> **限制：** `FScalableFloat` 的 `Curve` 成员（`CurveTableRowHandle` 类型）**没有** `PROPERTY()` 标签，`CurveTableRowHandle` 本身也未接入反射系统。因此 `Period.CurveTableName` 和 `Period.RowName` 等点分键写法**不生效**。曲线表功能需要在代码中手动设置 `Curve` 字段，或通过脚本操作。详见 [第 12 节](#12-curvetable曲线表) 和 [第 15 节](#15-已知限制)。

FScalableFloat 通过 `GetValueAtLevel(int32 Level)` 获取指定等级的值，若有 CurveTable 则线性插值。

### 5.8 结构字段速查

```ini
[Effect_XXX]
; 基础
DurationPolicy = Instant | Infinite | HasDuration
; DurationMagnitude / MaxDurationMagnitude 是 GameplayEffectModifierMagnitude（IniComponent），
; 用点分键配置，详见 5.9 节
DurationMagnitude.MagnitudeCalculationType = ScalableFloat
DurationMagnitude.ScalableFloatMagnitude = 10.0
; MaxDurationMagnitude同理（可选）
Period = 2.0                                    ; FScalableFloat，裸 float
bExecutePeriodicEffectOnApplication = yes
PeriodicInhibitionPolicy = NeverReset

; 修改器（指针数组，通过 section 名引用）
Modifiers = Mod_Section1, Mod_Section2

; 组件（指针数组，通过 section 名引用，$Type 指定子类型）
GEComponents = Comp_Section1, Comp_Section2

; 游戏提示
bRequireModifierSuccessToTriggerCues = yes

; 堆叠
StackingType = None | AggregateBySource | AggregateByTarget
StackLimitCount = 3
StackDurationRefreshPolicy = RefreshOnSuccessfulApplication
StackPeriodResetPolicy = NeverReset
StackExpirationPolicy = ClearEntireStack
bDenyOverflowApplication = no
bClearStackOnOverflow = no
bFactorInStackCount = no
bSuppressStackingCues = no
OverflowEffects = Effect_Overflow1, Effect_Overflow2    ; GE section 名
```

### 5.9 嵌套字段的点分键写法

GameplayEffect 中部分字段类型为 `IniComponent`（无 Parser 特化），这些字段通过**点分键**在当前 section 下展开子属性。支持多层嵌套，层数无限制。详见 [第 17 节 嵌套结构体 INI 加载](#17-嵌套结构体-ini-加载)。

#### 哪些字段用点分键，哪些不用

| 字段 | 类型 | 加载方式 | INI 写法 |
|---|---|---|---|
| DurationPolicy | enum | Parser（枚举名） | `DurationPolicy = HasDuration` |
| DurationMagnitude | GameplayEffectModifierMagnitude | **点分键**（IniComponent，无 Parser） | `DurationMagnitude.MagnitudeCalculationType = ScalableFloat` |
| MaxDurationMagnitude | GameplayEffectModifierMagnitude | **点分键** | 同上 |
| Period | FScalableFloat | Parser（裸 float） | `Period = 2.0` |
| bExecutePeriodicEffectOnApplication | bool | Parser | `bExecutePeriodicEffectOnApplication = yes` |
| PeriodicInhibitionPolicy | enum | Parser | `PeriodicInhibitionPolicy = NeverReset` |
| Modifiers | vector\<GameplayModifierInfo*\> | Parser（指针数组，section 名引用） | `Modifiers = Mod_Section1, Mod_Section2` |
| GEComponents | vector\<GameplayEffectComponent*\> | Parser（多态指针数组，section 名引用） | `GEComponents = Comp_Section1` |
| OverflowEffects | vector\<GameplayEffect*\> | Parser（指针数组，section 名引用） | `OverflowEffects = Effect_Overflow1` |
| StackingType | enum | Parser | `StackingType = AggregateBySource` |
| StackLimitCount | int32 | Parser | `StackLimitCount = 5` |
| 各 bool 字段 | bool | Parser | `bFactorInStackCount = yes` |

#### 单层嵌套：DurationMagnitude

`DurationMagnitude` 类型为 `GameplayEffectModifierMagnitude`（IniComponent），其子字段用 `DurationMagnitude.子字段名` 展开：

```ini
[Effect_Buff]
DurationPolicy = HasDuration
; ScalableFloat 方式（ScalableFloatMagnitude 有 Parser，读裸 float）
DurationMagnitude.MagnitudeCalculationType = ScalableFloat
DurationMagnitude.ScalableFloatMagnitude = 10.0

; SetByCaller 方式（SetByCallerMagnitude 有 Parser，读 GameplayTag）
DurationMagnitude.MagnitudeCalculationType = SetByCaller
DurationMagnitude.SetByCallerMagnitude = Damage.Amount
```

#### 多层嵌套：DurationMagnitude → AttributeBasedMagnitude → BackingAttribute

当 `MagnitudeCalculationType = AttributeBased` 时，`AttributeBasedMagnitude` 子字段本身也是 IniComponent，继续用点分键展开，形成多层嵌套：

```ini
[Effect_AttrBased]
DurationPolicy = HasDuration
DurationMagnitude.MagnitudeCalculationType = AttributeBased
; 第2层：AttributeBasedMagnitude 的子字段
DurationMagnitude.AttributeBasedMagnitude.Coefficient = 1.0
DurationMagnitude.AttributeBasedMagnitude.PreMultiplyAdditiveValue = 0.0
DurationMagnitude.AttributeBasedMagnitude.PostMultiplyAdditiveValue = 0.0
DurationMagnitude.AttributeBasedMagnitude.AttributeCalculationType = AttributeMagnitude
; 第3层：BackingAttribute（GameplayEffectAttributeCaptureDefinition）的子字段
DurationMagnitude.AttributeBasedMagnitude.BackingAttribute.AttributeToCapture = AttributeSet_Test.Health
DurationMagnitude.AttributeBasedMagnitude.BackingAttribute.AttributeSource = Source
DurationMagnitude.AttributeBasedMagnitude.BackingAttribute.bSnapshot = yes
; SourceTagFilter / TargetTagFilter 有 Parser（GameplayTagContainer），读逗号分隔标签
DurationMagnitude.AttributeBasedMagnitude.SourceTagFilter = Buff.Caster
DurationMagnitude.AttributeBasedMagnitude.TargetTagFilter = Debuff.Target
```

#### 点分键 vs section 引用

对于 IniComponent 类型的字段（无 Parser），除了点分键展开，也可以用 section 引用方式。两种方式不能混用，详见 [第 17 节](#17-嵌套结构体-ini-加载)：

```ini
; 方式1：点分键展开（推荐，简洁）
[Effect_Buff]
DurationMagnitude.MagnitudeCalculationType = ScalableFloat
DurationMagnitude.ScalableFloatMagnitude = 10.0

; 方式2：section 引用
[Effect_Buff]
DurationMagnitude = MagBuffDuration

[MagBuffDuration]
MagnitudeCalculationType = ScalableFloat
ScalableFloatMagnitude = 10.0
```

#### Modifier 内部的点分键

`GameplayModifierInfo` 本身是 `IniComponent`，其 `ModifierMagnitude` 子字段也是 `IniComponent`，同样支持多层点分键：

```ini
[Mod_HealHP]
; 第1层：GameplayModifierInfo 的直接子字段
Attribute = AttributeSet_Test.Health          ; GameplayAttribute 有 Parser
ModifierOp = AddBase                          ; enum 有 Parser
; 第2层：ModifierMagnitude（GameplayEffectModifierMagnitude）的子字段
ModifierMagnitude.MagnitudeCalculationType = ScalableFloat
ModifierMagnitude.ScalableFloatMagnitude = 50.0   ; FScalableFloat 有 Parser
; SourceTags / TargetTags 是 GameplayTagRequirements（IniComponent），支持点分键
; SourceTags.RequireTags = Alive
; SourceTags.IgnoreTags = Invincible
```

---

## 6. GEComponent（效果组件）

### 6.1 概念

GEComponent（效果组件）是附加到 GameplayEffect 上的模块化行为组件，没有自己的生命周期，通过挂接到所属 GE 的生命周期事件来工作。

### 6.2 全部 11 种类型

#### 1. TargetTagsGEComponent — 授予标签

GE 激活时向目标授予标签，移除时收回。

```ini
[Comp_GrantBuff]
$Type = TargetTagsGEComponent
GrantedTags = Buff.Speed, Buff.Strength
```

#### 2. AssetTagsGEComponent — 资产标签

为 GE 本身添加标签，用于查询和分类。

```ini
[Comp_AssetTag]
$Type = AssetTagsGEComponent
AssetTags = Effect.Buff, Effect.Physical
```

#### 3. BlockAbilityTagsGEComponent — 阻止能力

阻止带有指定标签的能力激活。使用 `FInheritedTagContainer`，支持父子继承（`Combined = Inherited - Removed + Added`）。嵌套结构体支持两种 INI 配置方式（详见 [第 17 节](#17-嵌套结构体-ini-加载)）：

```ini
; 方式1：点分键展开
[Comp_BlockAbility]
$Type = BlockAbilityTagsGEComponent
InheritableBlockedAbilityTagsContainer.Added = Ability.Attack, Ability.Special
; InheritableBlockedAbilityTagsContainer.Removed = Ability.Safe
; InheritableBlockedAbilityTagsContainer.Inherited = Ability.Base

; 方式2：section 引用
[Comp_BlockAbility]
$Type = BlockAbilityTagsGEComponent
InheritableBlockedAbilityTagsContainer = MyBlockedTags

[MyBlockedTags]
Added = Ability.Attack, Ability.Special
Removed = Ability.Safe
```

#### 4. CancelAbilityTagsGEComponent — 取消能力

取消正在运行的带有指定标签的能力。支持通过 `CancelMode` 控制在 GE 应用时、移除时或两者都取消。

```ini
[Comp_CancelAbility]
$Type = CancelAbilityTagsGEComponent
CancelAbilitiesWithTag = Ability.Concentration
CancelMode = CancelOnApply  ; CancelOnApply | CancelOnRemove | CancelBoth
```

#### 5. TagRequirementsGEComponent — 标签条件

GE 应用前检查目标/来源的标签条件。提供三组独立的 `GameplayTagRequirements`，分别控制应用、持续和移除阶段。每组含 `RequireTags`、`IgnoreTags` 和 `TagQuery`。嵌套结构体支持两种 INI 配置方式（详见 [第 17 节](#17-嵌套结构体-ini-加载)）：

```ini
; 方式1：点分键展开
[Comp_TagReq]
$Type = TagRequirementsGEComponent
ApplicationTagRequirements.RequireTags = Alive
ApplicationTagRequirements.IgnoreTags = Invincible
; OngoingTagRequirements.RequireTags = Alive
; OngoingTagRequirements.IgnoreTags = Dead
; RemovalTagRequirements.RequireTags = Debuff.Cleansable

; 方式2：section 引用
[Comp_TagReq]
$Type = TagRequirementsGEComponent
ApplicationTagRequirements = AppReq
OngoingTagRequirements = OngoingReq

[AppReq]
RequireTags = Alive
IgnoreTags = Invincible

[OngoingReq]
RequireTags = Alive
IgnoreTags = Dead
```

#### 6. GrantedAbilitiesGEComponent — 授予能力

GE 激活时向目标授予能力，移除时收回。通过 `GrantAbilityConfigs`（`vector<GameplayAbilitySpecDef>`）配置，每项包含 `Ability`、`LevelScalableFloat`、`InputID`、`RemovalPolicy` 等字段。也支持抑制状态变化时自动暂停/恢复。

```ini
[Comp_GrantAbility]
$Type = GrantedAbilitiesGEComponent
GrantAbilityConfigs = Ability_FireBreath:1:0:CancelAbilityImmediately
; 格式: AbilityDefine:Level:InputID:RemovalPolicy
```

#### 7. ImmunityGEComponent — 免疫

使目标免疫匹配的 GameplayEffect。通过 `ImmunityQueries`（`vector<FGameplayEffectQuery>`）配置，每个 query 支持按 EffectDef、SourceTags、TargetTags、EffectTags 等多维度匹配。

```ini
[Comp_Immunity]
$Type = ImmunityGEComponent
ImmunityQueries = Query1, Query2
; 每个 FGameplayEffectQuery 可配置: EffectDef, SourceTags, TargetTags, EffectTagsToMatch 等
; 简单用法: 直接指定要免疫的 GE 或标签
```

#### 8. ChanceToApplyGEComponent — 概率应用

GE 按概率应用。`ChanceToApplyToTarget` 为 `FScalableFloat` 类型，默认 1.0（始终应用），支持曲线表缩放。

```ini
[Comp_Chance]
$Type = ChanceToApplyGEComponent
ChanceToApplyToTarget = 0.5  ; 50% 概率
```

#### 9. RemoveOtherGEComponent — 移除其他 GE

GE 激活时移除其他指定 GE。通过 `RemoveGameplayEffectQueries`（`vector<FGameplayEffectQuery>`）配置，支持多维度匹配。

```ini
[Comp_RemoveOther]
$Type = RemoveOtherGEComponent
RemoveGameplayEffectQueries = Query1, Query2
; 每个 FGameplayEffectQuery 可配置: EffectDef, SourceTags, TargetTags 等
```

#### 10. CustomCanApplyGEComponent — 自定义检查

调用脚本函数决定 GE 是否可以应用。通过 `ApplicationRequirementCreators`（`vector<StringName>`）配置，每个 StringName 指向一个已注册的 ScriptFunction，迭代执行，任一返回 false 则阻止应用。

```ini
[Comp_CustomCheck]
$Type = CustomCanApplyGEComponent
ApplicationRequirementCreators = xkein/gas/can_apply_check
```

#### 11. AdditionalEffectsGEComponent — 连锁效果

GE 激活时额外应用其他 GE。提供 4 个 `vector<GameplayEffect*>` 字段，分别在不同时机触发：

| 字段 | 触发时机 |
|---|---|
| `OnApplicationGameplayEffects` | GE 成功应用时 |
| `OnCompleteAlways` | GE 移除时（无论原因） |
| `OnCompleteNormal` | GE 自然过期时 |
| `OnCompletePrematurely` | GE 被强制移除时 |

```ini
[Comp_Additional]
$Type = AdditionalEffectsGEComponent
OnApplicationGameplayEffects = Effect_SplashDamage
OnCompleteAlways = Effect_Cleanup
OnCompleteNormal = Effect_ExpireBonus
OnCompletePrematurely = Effect_Knockback
```

### 6.3 GEComponent 生命周期钩子

| 钩子 | 调用时机 | 可阻断 |
|---|---|---|
| CanGameplayEffectApply | GE 应用前检查 | 是 |
| OnActiveGameplayEffectAdded | GE 添加后 | 可抑制 |
| OnActiveGameplayEffectRemoved | GE 移除前 | 否 |
| OnGameplayEffectExecuted | Instant GE 执行时 | 否 |
| OnGameplayEffectApplied | GE 应用后（任何类型） | 否 |

---

## 7. AbilityTask（能力任务）

### 7.1 概念

AbilityTask（能力任务）是 GameplayAbility 内的异步任务单元，管理延迟、等待事件、属性监控等时间相关逻辑。任务在能力 PreActivate 阶段创建，在 EndAbility 时自动清理。

**生命周期：** Create → InitTask → Activate → (工作) → EndTask → ReadyForDestroy → 清理

### 7.2 全部 11 种任务

| 任务 | 说明 | 使用示例 |
|---|---|---|
| WaitDelay | 等待指定时间后触发 | `WaitDelay.Create(ability, 2.0).m_OnFinish.BindStdFunction(cb)` |
| WaitGameplayEvent | 等待指定标签的 gameplay 事件 | `WaitGameplayEvent.Create(ability, tag, true)` |
| WaitGameplayTagAdded | 等待指定标签被添加 | `WaitGameplayTagAdded.Create(ability, tag, true)` |
| WaitGameplayTagRemoved | 等待指定标签被移除 | `WaitGameplayTagRemoved.Create(ability, tag, true)` |
| WaitGameplayEffectApplied | 等待匹配 GE 被应用 | `WaitGameplayEffectApplied.Create(ability, query, true)` |
| WaitGameplayEffectRemoved | 等待指定 GE 被移除 | `WaitGameplayEffectRemoved.Create(ability, handle)` |
| WaitAttributeChange | 等待属性值变化 | `WaitAttributeChange.Create(ability, attr, true)` |
| WaitInput | 等待输入按下/释放 | `WaitInput.Create(ability, inputID, true, false)` |
| WaitTargetData | 等待目标选择完成 | `WaitTargetData.Create(ability)` |
| SpawnActor | 在指定位置生成单位 | `SpawnActor.Create(ability, type, loc)` |
| Repeat | 重复执行回调 | `Repeat.Create(ability, 5, 1.0)` |

各任务的回调委托：

| 任务 | 回调委托 |
|---|---|
| WaitDelay | `OnFinish` |
| WaitGameplayEvent | `OnEventReceived` |
| WaitGameplayTagAdded | `OnTagAdded` |
| WaitGameplayTagRemoved | `OnTagRemoved` |
| WaitGameplayEffectApplied | `OnEffectApplied` |
| WaitGameplayEffectRemoved | `OnEffectRemoved`, `OnInvalidHandle` |
| WaitAttributeChange | `OnAttributeChanged` |
| WaitInput | `OnInputPress`, `OnInputRelease` |
| WaitTargetData | `OnTargetDataReady`, `OnTargetDataCancelled` |
| SpawnActor | `OnSpawnComplete`, `OnSpawnFailed` |
| Repeat | `OnPerformAction`, `OnFinished` |

### 7.3 任务使用示例

```typescript
// 在能力激活中创建任务
ability.m_OnK2ActivateAbility.BindStdFunction(() => {
    // 延迟任务
    const delay = AbilityTask_WaitDelay.Create(ability, 1.5);
    delay.m_OnFinish.BindStdFunction(() => {
        console.log("delayed action");
    });

    // 等待标签
    const waitTag = AbilityTask_WaitGameplayTagAdded.Create(ability, tag, true);
    waitTag.m_OnTagAdded.BindStdFunction(() => {
        console.log("tag received");
    });

    // 创建即可，PreActivate 会自动调用 Activate()
});
```

---

## 8. AbilitySystemComponent（ASC）

### 8.1 概念

AbilitySystemComponent（能力系统组件，简称 ASC）是 GAS 的中枢，挂载在游戏单位上，管理该单位的所有属性、能力和效果。

### 8.2 INI 配置

```ini
[HTK]  ; TechnoType
; ASC 全局配置挂在 TechnoType 上
ASC.Attributes = AttributeSet_Base, AttributeSet_Combat
ASC.DefaultAbilities = Ability_Attack, Ability_Defend, Ability_Special
ASC.StartupTags = HTKTag, Player.Controllable
ASC.StartupEffects = Effect_BaseStats, Effect_PassiveRegen
```

对应 C++ 类型 `AbilitySystemComponentType`，自动加载到 TechnoTypeClass 上。

### 8.3 初始化流程

```
单位创建 → OnEntityConstruct
  ├─ 创建 AbilitySystemComponent 实例
  ├─ InitializeFromType
  │   ├─ 读取 ASC.Attributes → AddAttributeSet 创建属性集
  │   ├─ 读取 ASC.StartupTags → AddLooseGameplayTag
  │   ├─ 读取 ASC.DefaultAbilities → GiveAbility
  │   └─ 读取 ASC.StartupEffects → ApplyGameplayEffectToSelf
  └─ 单位就绪
```

### 8.4 脚本 API 表

| 方法 | 说明 |
|---|---|
| `GiveAbility(spec)` | 授予能力，返回 handle |
| `GiveAbility(define)` | 按定义授予能力 |
| `GiveAbilityAndActivateOnce(spec, eventData?)` | 授予并立即激活一次 |
| `TryActivateAbility(handle)` | 尝试激活能力 |
| `TryActivateAbilityByDefine(define)` | 按定义激活能力 |
| `TriggerAbilityFromGameplayEvent(handle, eventData)` | 从事件触发能力 |
| `CancelAbility(ability)` | 取消指定能力 |
| `RemoveAbility(handle)` | 移除能力 |
| `ApplyGameplayEffectToTarget(effect, target, context)` | 对目标应用 GE |
| `ApplyGameplayEffectToSelf(effect, context)` | 对自己应用 GE |
| `MakeEffectContext()` | 创建效果上下文 |
| `ExecuteGameplayCue(tag, params?)` | 执行一次 gameplay cue |
| `AddGameplayCue(tag, params?)` | 添加持续 gameplay cue |
| `RemoveGameplayCue(tag)` | 移除持续 gameplay cue |
| `AssignSetByCallerMagnitude(handle, name, mag)` | 设置 SetByCaller 数值 |
| `AssignTagSetByCallerMagnitude(handle, tag, mag)` | 按标签设置数值 |

### 8.5 事件委托表

所有委托均为 `PROPERTY()` 类型的 `TMulticastDelegate`，可从 TypeScript 绑定：

- `AddStdFunction(fn)` — 绑定 JS lambda，不可存档
- `AddScriptFunction(category, name)` — 绑定已注册的 ScriptFunction，可存档（存档时保存 FuncId，读档时按 FuncId 恢复绑定）

| 委托 | 签名 | 说明 |
|---|---|---|
| OnGameplayEffectAppliedDelegateToSelf | (asc, spec, handle) | GE 对自己应用时 |
| OnGameplayEffectAppliedDelegateToTarget | (asc, spec, handle) | 自己对目标应用 GE 时 |
| OnActiveGameplayEffectAddedDelegateToSelf | (asc, spec, handle) | 持续 GE 添加时 |
| OnPeriodicGameplayEffectExecuteDelegateOnSelf | (asc, spec, handle) | 周期 GE 对自己执行时 |
| OnPeriodicGameplayEffectExecuteDelegateOnTarget | (asc, spec, handle) | 周期 GE 对目标执行时 |
| AbilityFailedCallbacks | (asc, ability, failureTags) | 能力激活失败时 |
| AbilityEndedCallbacks | (asc, ability) | 能力结束时 |
| AbilityActivatedCallbacks | (asc, handle, ability) | 能力激活时 |
| AbilityCommittedCallbacks | (asc, handle, ability) | 能力提交时 |
| AbilitySpecDirtiedCallbacks | (asc, spec) | 能力 spec 变脏时 |
| OnImmunityBlockGameplayEffectDelegate | (asc, spec, activeGE) | 免疫阻止 GE 时 |

> **存档说明：** ASC 上的 multicast delegate 现在支持存档。使用 `AddScriptFunction(category, name)` 绑定的回调在存档时会保存 FuncId，读档时按 FuncId 恢复绑定。使用 `AddStdFunction(fn)` 绑定的 JS lambda 不可存档，存档时会记录警告并跳过，读档后该绑定丢失。详见[第 16 节 委托存档](#16-委托存档delegate-savegame)。

---

## 9. GameplayCue（游戏提示）

### 9.1 概念

GameplayCue（游戏提示）是轻量级的音频/视觉反馈系统，与游戏逻辑解耦。用于处理命中特效、技能音效等表现层内容。

### 9.2 事件类型

| 事件 | 说明 |
|---|---|
| Executed （执行） | 一次性触发（Instant GE） |
| OnActive （激活） | 持续效果开始 |
| WhileActive （持续中） | 持续效果进行中 |
| Removed （移除） | 持续效果结束 |

### 9.3 GameplayCueParameters（参数）

```typescript
const params = new GameplayCueParameters();
params.m_NormalizedMagnitude = 1.0;
params.m_RawMagnitude = 50.0;
params.m_Location = new Vector3D(100, 200, 0);
params.m_Instigator = sourceEntity;
params.m_EffectCauser = causerEntity;
params.m_GameplayEffectLevel = 1;
params.m_AbilityLevel = 1;
```

### 9.4 Notify 类型

系统中有两类 Notify：**INI 定义的 Define** 和 **C++ 运行时类**。

#### INI Define 类型（通过 `[GameplayCue.XXX]` 配置）

| 类型 | 说明 |
|---|---|
| **GameplayCueNotifyDefine_Static** | 无状态，支持 Wwise 音频 + 动画，响应所有事件 |
| **GameplayCueNotifyDefine_Burst** | 只响应 Executed 事件 |
| **GameplayCueNotifyDefine_Actor** | 有状态，支持持续性循环动画（LoopingAnim） |
| **GameplayCueNotifyDefine_BurstLatent** | 有状态，只响应 Executed，带延迟，继承 Actor |

#### C++ 运行时类

| 类 | 说明 |
|---|---|
| **GameplayCueNotify_Static** | 无状态一次性 Cue，`OnExecute()` / `OnActive()` / `OnRemove()` |
| **GameplayCueNotify_Burst** | 继承 Static，数组化 BurstEffects，覆盖 `OnExecute()` |
| **GameplayCueNotify_Actor** | 有状态持续 Cue，支持 `OnBurst()` / `OnBecomeRelevant()` / `OnCeaseRelevant()` |
| **GameplayCueNotify_BurstLatent** | 继承 Actor，带 `OnK2_OnBurst` TDelegate（JS 可重写） |
| **GameplayCueNotify_Looping** | 继承 Actor，**四阶段效果模型**：ApplicationEffects（应用时）、LoopingEffects（持续中）、RecurringEffects（周期性）、RemovalEffects（移除时） |

#### Custom 脚本变体（带 TDelegate 回调）

| 类 | 可绑定的回调 |
|---|---|
| **CustomGameplayCueNotify_Static** | `OnK2_OnExecute`, `OnK2_OnActive`, `OnK2_OnRemove` |
| **CustomGameplayCueNotify_BurstLatent** | `OnK2_OnBurst` |
| **CustomGameplayCueNotify_Looping** | `OnK2_OnBurst`, `OnK2_OnBecomeRelevant`, `OnK2_OnCeaseRelevant` |

### 9.5 INI 配置

```ini
[GameplayCue.Impact.Explosion]
$Type = GameplayCueNotifyDefine_Static
GameplayCueTag = Cue.Impact.Explosion
WwiseEventName = Explosion_Small
BurstAnim = ANIM_EXPLOSION

[GameplayCue.Buff.Shield]
$Type = GameplayCueNotifyDefine_Actor
GameplayCueTag = Cue.Buff.Shield
LoopingAnim = ANIM_SHIELD
bAutoDestroyOnRemove = true
```

### 9.6 脚本触发

```typescript
// 一次性 cue
asc.ExecuteGameplayCue(tag);

// 持续 cue
asc.AddGameplayCue(tag, params);
// ... 稍后移除
asc.RemoveGameplayCue(tag);

// 检查是否激活
asc.IsGameplayCueActive(tag);
```

### 9.7 子类型

INI Define 子类型：

| 定义类 | 说明 |
|---|---|
| GameplayCueNotifyDefine_Static | 无状态，支持音频+动画 |
| GameplayCueNotifyDefine_Burst | 只响应 Executed 事件 |
| GameplayCueNotifyDefine_Actor | 有状态，支持持续性循环动画 |
| GameplayCueNotifyDefine_BurstLatent | 有状态，只响应 Executed，带延迟 |

C++ 运行时类和 Custom 脚本变体见 [9.4 节](#94-notify-类型)。

---

## 10. 属性聚合系统

### 10.1 概念

FAggregator（属性聚合器）是 GAS 中负责组合所有 Modifier 并计算属性最终值的系统。每个被 GE 修改的属性都有一个对应的 FAggregator。代码移植自 UE 5.8 GAS FAggregator。

### 10.2 通道系统（EGameplayModEvaluationChannel）

FAggregator 使用 **10 个求值通道**（Channel0 ~ Channel9）来分层应用 modifier。通道按数值顺序求值，前一通道的输出作为后一通道的输入。

```
BaseValue → Channel0 求值 → Channel1 求值 → ... → Channel9 求值 → 最终值
```

例如：BaseValue = 2，Channel0 有一个 +2 AddBase modifier，则 Channel1 接收到的 base value 为 4。

大多数情况下 modifier 都在 Channel0 上，多通道用于需要分阶段计算的高级场景。

### 10.3 单通道计算公式

每个通道内部的计算公式：

```
((Base + Sum(AddBase))
    × (1 + Sum(MultiplyAdditive))
    ÷ (1 + Sum(DivideAdditive))
    × Product(MultiplyCompound))
    + Sum(AddFinal)
```

特殊情况：如果该通道内存在 Override 类型的 modifier，第一个符合条件的 Override modifier 直接返回，忽略其他计算。

### 10.4 核心组件

| 组件 | 说明 |
|---|---|
| `FAggregator` | 核心聚合器，持有 BaseValue 和 ModChannels，提供求值、modifier 管理、快照、依赖跟踪 |
| `FAggregatorMod` | 单个 modifier 条目，含 EvaluatedMagnitude、SourceTagReqs、TargetTagReqs、ActiveHandle |
| `FAggregatorModChannel` | 单通道，持有按 ModOp 分类的 modifier 数组，提供 `EvaluateWithBase()` |
| `FAggregatorModChannelContainer` | 通道容器（map<Channel, ModChannel>），按数值顺序链式求值 |
| `FAggregatorEvaluateParameters` | 求值参数，控制 modifier 资格（SourceTags、TargetTags、IgnoreHandles、过滤标签） |
| `FAggregatorRef` | shared_ptr 包装，提供快照语义 |
| `FScopedAggregatorOnDirtyBatch` | 批量锁，延迟 OnDirty 广播，避免多次 modifier 修改时的冗余重算 |

### 10.5 Modifier 资格检查（Qualification）

每个 modifier 在求值前会经过资格检查（`UpdateQualifies`），基于以下条件判断是否参与计算：

- SourceTagReqs / TargetTagReqs — 来源/目标的标签需求
- IgnoreHandles — 需要跳过的 GE 句柄
- AppliedSourceTagFilter / AppliedTargetTagFilter — 应用的来源/目标标签过滤
- IncludePredictiveMods — 是否包含预测 modifier（帧同步环境下始终为 false）

### 10.6 属性捕获系统（FGameplayEffectAttributeCaptureSpec）

用于 Execution 类型的 GE，在执行时捕获属性值：

- `CaptureAttributes(ASC, CaptureSource)` — 从 ASC 捕获属性，分 Source/Target 两区
- `AttemptCalculateAttributeMagnitude()` — 计算属性最终值
- `AttemptCalculateAttributeBaseValue()` — 获取属性基础值
- `AttemptCalculateAttributeBonusMagnitude()` — 计算 bonus（最终值 - 基础值）
- `AttemptCalculateAttributeContributionMagnitude()` — 计算指定 GE 的贡献值
- `AttemptGetAttributeAggregatorSnapshot()` — 获取聚合器快照（深拷贝）
- 支持 Snapshot（捕获时固定值）和非 Snapshot（实时读取）两种模式

### 10.7 快照与依赖跟踪

- `TakeSnapshotOf()` — 深拷贝另一个聚合器的状态（BaseValue + 所有通道 modifier）
- `AddDependent(handle)` — 注册依赖的 GE 句柄，当聚合器变化时通知依赖方
- `OnDirty` 委托 — 聚合器变脏时广播，可被 `FScopedAggregatorOnDirtyBatch` 延迟

### 10.8 计算过程

```
FAggregator::Evaluate(Parameters)
  ├─ EvaluateQualificationForAllMods(Parameters) — 更新所有 modifier 的资格
  └─ ModChannels.EvaluateWithBase(BaseValue, Parameters)
       ├─ 按 Channel0 → Channel9 顺序遍历
       ├─ 每个 Channel: 检查 Override → 按公式计算 → 输出作为下个 Channel 的 base
       └─ 返回最终值
```

### 10.9 聚合器生命周期

```
属性被 GE 修改
  └─ FindOrCreateAttributeAggregator(attribute)
       ├─ 从 AttributeDataMap 获取 BaseValue
       ├─ 注册 OnDirty 回调 → OnAttributeAggregatorDirty
       └─ 插入 AttributeAggregatorMap

GE 移除时
  └─ RemoveActiveGameplayEffectGrantedTagsAndModifiers
       └─ RemoveAggregatorMod → 从聚合器移除 modifier
            └─ 触发 OnDirty → 重新计算属性值
```

---

## 11. SetByCaller

### 11.1 概念

SetByCaller（由调用者设置）是一种动态数值机制，允许在运行时指定修改器数值，而不是在 INI 中固定。

### 11.2 两种标识方式

| 方式 | 字段 | 说明 |
|---|---|---|
| 标签方式（推荐） | DataTag | 使用 GameplayTag 标识 |
| 名称方式（已废弃） | DataName | 使用 StringName 标识 |

### 11.3 INI 配置

```ini
; 在 Effect 中声明使用 SetByCaller
[Effect_DamageVariable]
Modifiers = Mod_DamageVar

[Mod_DamageVar]
Attribute = AttributeSet_Test.Health
ModifierOp = AddBase
; ModifierMagnitude 是嵌套 IniComponent，用点分键配置
ModifierMagnitude.MagnitudeCalculationType = SetByCaller
; SetByCallerMagnitude 有 Parser，直接读 GameplayTag 名称
ModifierMagnitude.SetByCallerMagnitude = Damage.Amount
```

SetByCaller 不仅可用于 Modifier，也可用于 Duration 和 MaxDuration。在 `DurationMagnitude` 或 `MaxDurationMagnitude` 中设置 `MagnitudeCalculationType = SetByCaller` 即可。

### 11.4 脚本 API

```typescript
// 创建 GE spec 并设置值
const handle = asc.ApplyGameplayEffectToTarget(effect, target, context);

// 按标签设置
asc.AssignTagSetByCallerMagnitude(handle, tag, 100.0);

// 按名称设置（已废弃）
asc.AssignSetByCallerMagnitude(handle, name, 100.0);
```

### 11.5 存储

Spec 内部有两个 map 存储 SetByCaller 数值：

```cpp
// GameplayEffectSpec 中
std::map<GameplayTag, float> SetByCallerMagnitudes;      // 标签方式
std::map<StringName, float> SetByCallerNameMagnitudes;   // 名称方式（已废弃）
```

---

## 12. CurveTable（曲线表）

### 12.1 概念

CurveTable（曲线表）提供等级相关的数值缩放。在 INI 中定义，由 AbilitySystemGlobals 加载，被 FScalableFloat 引用。

### 12.2 INI 格式

```ini
[CurveTable.BuffDuration]
1 = 2.0
2 = 2.5
3 = 3.0
5 = 5.0
10 = 10.0

[CurveTable.DamageScale]
1 = 1.0
3 = 1.5
5 = 2.0
10 = 3.5
```

### 12.3 自动加载

所有 `[CurveTable.XXX]` 节会在 INI 加载时自动被 AbilitySystemGlobals 解析：

```cpp
// 匹配以 "CurveTable." 开头的节
// 提取节名去除前缀作为 tableName
// 每行：level = value
```

### 12.4 引用曲线表

> **重要限制：** `FScalableFloat` 的 `Curve` 成员（`CurveTableRowHandle` 类型）没有 `PROPERTY()` 标签，且 `FScalableFloat` 有 `Parser<FScalableFloat>` 特化（只读裸 float）。因此以下写法**均不生效**：
> - `Period.CurveTableName = BuffDuration`（点分键不生效，因为 FScalableFloat 走 Parser 路径）
> - `ScalableFloatMagnitude.CurveTableName = BuffDuration`（同理，FScalableFloat 在 IniComponent 内部仍走 Parser）
>
> 曲线表目前只能通过**代码或脚本**手动设置 `FScalableFloat::Curve.CurveTableName` 字段来使用。INI 中 `FScalableFloat` 字段只能写裸 float 值（如 `Period = 2.0`）。

```ini
; INI 中只能这样写（裸 float）
[Effect_LevelBuff]
DurationPolicy = HasDuration
Period = 2.0
```

```typescript
// 通过脚本设置曲线表
const effect = GameplayEffect.FindOrAllocate("Effect_LevelBuff");
effect.m_Period.m_Curve.m_CurveTableName = new StringName("BuffDuration");
// RowName 被读取但未实际用于查找（见下方限制）
```

> **当前限制：** `GetValueAtLevel()` 实现中只使用 `CurveTableName` 查找曲线表，`RowName` 被读取但**未实际用于查找**。曲线表的数据结构为 `map<StringName, map<int32, float>>`（表名 → 单条曲线），没有 Row 维度。这意味着每个 `[CurveTable.XXX]` 节只能定义一条曲线。如果多个属性需要不同曲线，请使用不同的 `[CurveTable.XXX]` 节名。

### 12.5 GetValueAtLevel 行为

```cpp
FScalableFloat::GetValueAtLevel(int32 Level)
{
    if (CurveTable 有效) {
        // 在 CurveTable 中查找 RowName 对应的曲线
        // 如果 Level 在两个关键帧之间，线性插值
        // 如果 Level 超出范围，使用最近的关键帧值
    }
    return Value; // 没有曲线表时返回固定值
}
```

---

## 13. INI 配置完整参考

### 13.1 [GAS] — 全局设置

```ini
[GAS]
DefaultAttributeSets = AttrSet1, AttrSet2
ActivateFailCanActivateAbilityTag = Ability.ActivateFail
```

### 13.2 [AttributeSet_XXX] — 属性集定义

```ini
[AttributeSet_Player]
AttributeSetCreator = xkein/gas/player_attr
Attributes = Health, MaxHealth, Mana, MaxMana, Attack, Defense
```

### 13.3 [Ability_XXX] — 能力定义

```ini
[Ability_Fireball]
AbilityCreator = xkein/gas/abilities/fireball
AbilityTags = Ability.Attack, Ability.Magic
InstancingPolicy = InstancedPerActor
bRetriggerInstancedAbility = false
CostGameplayEffectClass = Effect_FireballCost
CooldownGameplayEffectClass = Effect_FireballCooldown
AbilityTriggers = Event.Fireball:GameplayEvent
CancelAbilitiesWithTag = Ability.Concentration
BlockAbilitiesWithTag = Ability.Stunned
ActivationOwnedTags = Buff.Casting
ActivationRequiredTags = Alive, CanAct
ActivationBlockedTags = Debuff.Stun, Debuff.Silence
SourceRequiredTags = Player.Ally
SourceBlockedTags = Player.Enemy
TargetRequiredTags = Enemy
TargetBlockedTags = Ally, Invincible
```

### 13.4 [Effect_XXX] — 游戏效果定义

```ini
[Effect_Heal]
DurationPolicy = Instant
Modifiers = Mod_HealHP

[Mod_HealHP]
Attribute = AttributeSet_Player.Health
ModifierOp = AddBase
ModifierMagnitude.MagnitudeCalculationType = ScalableFloat
ModifierMagnitude.ScalableFloatMagnitude = 30.0

[Effect_Slow]
DurationPolicy = HasDuration
DurationMagnitude.MagnitudeCalculationType = ScalableFloat
DurationMagnitude.ScalableFloatMagnitude = 5.0
Modifiers = Mod_SlowSpeed
Period = 0
GEComponents = Comp_SlowTag

[Mod_SlowSpeed]
Attribute = AttributeSet_Player.Speed
ModifierOp = MultiplyAdditive
ModifierMagnitude.MagnitudeCalculationType = ScalableFloat
ModifierMagnitude.ScalableFloatMagnitude = -0.5

[Effect_Regen]
DurationPolicy = Infinite
Period = 1.0
bExecutePeriodicEffectOnApplication = yes
Modifiers = Mod_RegenHP

[Mod_RegenHP]
Attribute = AttributeSet_Player.Health
ModifierOp = AddBase
ModifierMagnitude.MagnitudeCalculationType = ScalableFloat
ModifierMagnitude.ScalableFloatMagnitude = 5.0
```

### 13.5 GE 组件

```ini
[Comp_GrantBuff]
$Type = TargetTagsGEComponent
GrantedTags = Buff.Regeneration

[Comp_BlockStun]
$Type = BlockAbilityTagsGEComponent
; 可用点分键：InheritableBlockedAbilityTagsContainer.Added = Ability.Stun
; 也可用 section 引用：InheritableBlockedAbilityTagsContainer = BlockedTagsSection
InheritableBlockedAbilityTagsContainer.Added = Ability.Stun

[Comp_ChanceHalf]
$Type = ChanceToApplyGEComponent
ChanceToApplyToTarget = 0.5
```

### 13.6 [CurveTable.XXX] — 曲线表

```ini
[CurveTable.DamagePerLevel]
1 = 10
2 = 15
3 = 22
5 = 40
10 = 100
```

### 13.7 [TechnoType] ASC 配置

```ini
[MTNK]  ; 犀牛坦克
ASC.Attributes = AttributeSet_Base, AttributeSet_Combat
ASC.DefaultAbilities = Ability_Move, Ability_Attack, Ability_Defense
ASC.StartupTags = Vehicle, Tank, PlayerControlled
ASC.StartupEffects = Effect_BaseStats
```

---

## 14. 快速开始

### 步骤 1：定义属性

```ini
; rules.ini
[AttributeSet_Test]
AttributeSetCreator = xkein/gas/test_attr
Attributes = HP, MaxHP, MP, MaxMP
```

### 步骤 2：创建属性集脚本

```typescript
// src/scripts/typescript/xkein/gas/test_attr.ts
import { CustomAttributeSet, AttributeSet, AttributeSetDefine, AbilitySystemComponent } from "XkeinExt";

export function attribute_set_creator(define: AttributeSetDefine, com: AbilitySystemComponent): AttributeSet {
    const set = CustomAttributeSet.Create();
    return set;
}
```

### 步骤 3：定义能力

```ini
[Ability_TestHeal]
AbilityCreator = xkein/gas/abilities/test_heal
InstancingPolicy = InstancedPerActor
ActivationOwnedTags = Buff.Healing
ActivationRequiredTags = Alive
ActivationBlockedTags = Debuff.Stun
CostGameplayEffectClass = Effect_HealCost
```

### 步骤 4：创建能力脚本

```typescript
// src/scripts/typescript/xkein/gas/abilities/test_heal.ts
import {
    CustomGameplayAbility, GameplayAbility, GameplayAbilityDefine,
    AbilitySystemComponent, GameplayEffect, AbilityTask_WaitDelay,
    GameplayEffectContextHandle
} from "XkeinExt";

export function ability_creator(define: GameplayAbilityDefine, com: AbilitySystemComponent): GameplayAbility {
    const ability = CustomGameplayAbility.Create();

    ability.m_OnK2ActivateAbility.BindStdFunction(() => {
        const targetASC = ability.GetAbilitySystemComponentFromActorInfo();
        if (!targetASC) return;

        // 应用治疗效果
        const ctx = targetASC.MakeEffectContext();
        targetASC.ApplyGameplayEffectToSelf(define.m_CostGameplayEffectClass, ctx);

        // 延迟效果
        const delay = AbilityTask_WaitDelay.Create(ability, 0.5);
        delay.m_OnFinish.BindStdFunction(() => {
            ability.K2_EndAbility();
        });
    });

    return ability;
}
```

### 步骤 5：挂载到单位

```ini
[E1]  ; 美国大兵
ASC.Attributes = AttributeSet_Test
ASC.DefaultAbilities = Ability_TestHeal
ASC.StartupTags = Infantry, PlayerControlled
```

### 注册脚本加载器

```typescript
// src/scripts/typescript/xkein/gas.ts
import { setupGas } from "./gas";

export function setupGas() {
    ScriptFunctionRegister.RegisterLoader(
        GameplayAbilitySystem.s_ScriptFunctionCategoryAbility,
        (name) => {
            const m = require(name);
            if (m && m.ability_creator) return new GameplayAbilityCreator(m.ability_creator);
        }
    );
    // ... 属性集和任务的加载器类似
}
```

---

## 15. 已知限制

### 15.1 CueNotify CDO 注册未暴露

GameplayCueNotify 的 CDO（类默认对象）注册机制还没有完全在脚本层暴露。目前通过 `GameplayCueNotify_Static.CreateInstance()` 和 `GameplayCueNotify_Actor.CreateInstance()` 工厂方法创建实例，但完整的 CDO 注册管道在脚本层尚不可用。

**影响：** 无法在 TypeScript 中定义新的 GameplayCueNotify 子类并自动注册，但可以通过 INI 定义（`GameplayCueNotifyDefine_Static` / `GameplayCueNotifyDefine_Actor`）和脚本工厂函数配合使用已有的 C++ 类型。

**替代方案：** 使用 INI 定义 `[GameplayCue.XXX]` 配合 `$Type` 指定预设类型。

### 15.2 TechnoClass.GetTarget() 未在 TS 绑定中暴露

`TechnoClass` 上的 `GetTarget()` 方法还没有在 TypeScript 类型绑定中暴露。

**影响：** 在脚本层获取单位当前目标时，需要使用变通方法（如通过 `XkeinTools.FindFirstTarget` 或者遍历查询）。

```typescript
// 当前变通方案
const target = XkeinTools.FindFirstTarget(new QuerySphere(location, radius, QueryFlags.Techno));
```

### 15.3 Per-Active-Effect 事件委托未暴露给脚本

每个活跃 GE 有一组按句柄的事件委托（`FActiveGameplayEffectEvents`），包括 `OnRemoved`、`OnStackChanged`、`OnTimeChanged`、`OnInhibitionChanged`，以及 ASC 上的访问器方法（`OnGameplayEffectRemoved_InfoDelegate`、`OnGameplayEffectStackChangeDelegate`、`OnGameplayEffectTimeChangeDelegate`、`OnGameplayEffectInhibitionChangedDelegate`）。这些目前未在脚本层直接暴露。

**影响：** 无法在 TypeScript 中监听某个特定活跃 GE 的移除、堆叠变化、时间变化或抑制状态变化事件。

```cpp
// C++ API（当前脚本不可达）
FOnActiveGameplayEffectRemoved_Info* ASC.OnGameplayEffectRemoved_InfoDelegate(Handle);
FOnActiveGameplayEffectStackChange* ASC.OnGameplayEffectStackChangeDelegate(Handle);
FOnActiveGameplayEffectTimeChange* ASC.OnGameplayEffectTimeChangeDelegate(Handle);
FOnActiveGameplayEffectInhibitionChanged* ASC.OnGameplayEffectInhibitionChangedDelegate(Handle);
```

**替代方案：** 使用 `OnActiveGameplayEffectAddedDelegateToSelf` 配合 `AbilityTask_WaitGameplayEffectRemoved` 任务来监听特定 GE 的移除。堆叠和时间变化目前无直接替代方案。

### 15.4 其他注意事项

- 项目使用帧同步（Deterministic Lockstep），因此所有网络复制相关的 API（如 `bReplicateEndAbility`）在帧同步环境下行为不同
- `AbilityTask_WaitAttributeChange` 当前使用轮询方式实现，后续应迁移到事件驱动
- `AbilityTask_WaitInput` 当前也是轮询方式，后续应迁移到委托驱动
- `FScalableFloat` 的 `operator float()` 允许隐式转换，但需要注意当 CurveTable 设置后，直接使用 float 值会忽略曲线表缩放
- 命名方式（DataName）的 SetByCaller 已经废弃，请优先使用标签方式（DataTag）
- `AttributeSetDefine` 的 `AttributeSetCreator` 指向脚本路径，目前通过 `ScriptFunctionRegister` 的 loader 模式加载
- **FScalableFloat CurveTable 无法从 INI 加载**：`FScalableFloat` 的 `Curve` 成员没有 `PROPERTY()` 标签，且有 `Parser<FScalableFloat>` 特化（只读裸 float）。INI 中 `Period.CurveTableName` 等点分键写法不生效，只能写裸 float（如 `Period = 2.0`）。曲线表需通过代码或脚本手动设置（详见 [第 12 节](#12-curvetable曲线表)）
- **CurveTable RowName 未实现**：`GetValueAtLevel()` 只使用 `CurveTableName` 查找，`RowName` 被读取但未用于查找。每个 `[CurveTable.XXX]` 节只能定义一条曲线（详见 [第 12 节](#12-curvetable曲线表)）
- **GameplayEffect 的 GameplayCues 字段无法从 INI 加载**：`GameplayEffectCue` 只有 `CLASS(BindJs)`，不是 `IniComponent` / `IniAutoLoad`，也没有 `Parser` 特化。`GameplayCues` 字段（`vector<GameplayEffectCue*>`）的指针解析会失败。Cue 触发应通过 `[GameplayCue.XXX]` INI 定义和 GameplayCueTag 机制实现（详见 [第 9 节](#9-gameplaycue游戏提示)）
- **GameplayEffect 的 Executions 字段无法从 INI 加载**：`GameplayEffectExecutionDefinition` 只有 `CLASS(BindJs)`，不是 `IniComponent` / `IniAutoLoad`，也没有 `Parser` 特化。`Executions` 字段（`vector<GameplayEffectExecutionDefinition>`）的解析会失败。自定义 Execution 需通过脚本设置
- `ChanceToApplyGEComponent` 使用 `rand()` 进行概率判定，帧同步环境下可能需要替换为基于种子的确定性随机

### 15.5 委托回调 API 变更（Breaking Change）

GAS 中所有 `std::function` 类型的回调成员已迁移到 `TDelegate` / `TMulticastDelegate`。这是一次 **破坏性 JS API 变更**，用户需要更新现有的 TS 脚本。

**旧写法（已失效）：**

```typescript
// 直接赋值 — 不再编译通过
ability.m_OnK2ActivateAbility = someCallback;
delay.m_OnFinish = someCallback;
```

**新写法：**

```typescript
ability.m_OnK2ActivateAbility.BindStdFunction(() => { /* ... */ });
delay.m_OnFinish.BindStdFunction(() => { /* ... */ });
```

对于 ASC 上的 multicast delegate（见 [8.5 事件委托表](#85-事件委托表)），使用 `AddStdFunction` 代替直接赋值：

```typescript
asc.OnAbilityEndedCallbacks.AddStdFunction((ability) => { /* ... */ });
```

**迁移要点：**

- 单播委托（`TDelegate`）：`obj.m_OnXxx = fn` → `obj.m_OnXxx.BindStdFunction(fn)`
- 多播委托（`TMulticastDelegate`）：`obj.OnXxx = fn` → `obj.OnXxx.AddStdFunction(fn)`
- 闭包结尾从 `};` 变为 `});`（因为现在是方法调用）
- 如需存档兼容，改用 `BindScriptFunction` / `AddScriptFunction`，详见[第 16 节](#16-委托存档delegate-savegame)

---

## 16. 委托存档（Delegate Savegame）

GAS 的委托系统支持存档序列化，但不同绑定方式的存档行为不同。选择正确的绑定方式取决于回调是否需要在存档/读档后存活。

### 16.1 两种绑定方式

#### BindStdFunction(fn) — JS lambda 绑定，不可存档

```typescript
// 绑定一个 JS lambda（闭包）
ability.m_OnK2ActivateAbility.BindStdFunction(() => {
    console.log("activated");
});
```

- **存档时：** 记录一条警告日志，跳过该绑定（不写入任何数据）
- **读档后：** 委托处于 unbound 状态，回调不会触发
- **适用场景：** 临时回调，不需要跨存档存活。大部分游戏内即时逻辑用这种方式即可

#### BindScriptFunction(category, name) — 已注册 ScriptFunction 绑定，可存档

```typescript
// 绑定一个已注册的 ScriptFunction（按 category + name 查找）
ability.m_OnK2ActivateAbility.BindScriptFunction(
    GameplayAbilitySystem.s_ScriptFunctionCategoryAbility,
    "test_heal/OnActivateAbility"
);
```

- **存档时：** 保存 ScriptFunction 的 FuncId
- **读档后：** 按 FuncId 查找 ScriptFunction 并恢复绑定
- **前提条件：** 对应的 ScriptFunction 必须在存档前和读档前都通过 `ScriptFunctionRegister.RegisterFunction` 注册
- **适用场景：** 需要跨存档存活的回调，例如持久化能力的激活逻辑

### 16.2 Multicast Delegate 的存档

ASC 上的 multicast delegate（见 [8.5 事件委托表](#85-事件委托表)）使用 `AddStdFunction` / `AddScriptFunction`，行为与单播委托一致：

```typescript
// 不可存档 — JS lambda
asc.OnAbilityEndedCallbacks.AddStdFunction((ability) => {
    console.log("ability ended");
});

// 可存档 — 已注册 ScriptFunction
asc.OnAbilityEndedCallbacks.AddScriptFunction(
    GameplayAbilitySystem.s_ScriptFunctionCategoryAbility,
    "my_module/OnAbilityEnded"
);
```

### 16.3 ScriptFunction 注册

使用 `BindScriptFunction` / `AddScriptFunction` 前，必须先注册 ScriptFunction：

```typescript
// 注册（在脚本加载阶段完成，存档和读档前都需保证已注册）
ScriptFunctionRegister.RegisterFunction(
    GameplayAbilitySystem.s_ScriptFunctionCategoryAbility,
    "test_heal/OnActivateAbility",
    () => {
        // 回调逻辑
    }
);
```

注册时机很关键。存档前注册是为了让系统能找到 FuncId。读档前注册是为了让系统能按 FuncId 恢复绑定。通常在脚本加载阶段统一注册即可满足两者。

### 16.4 AbilityTask 的自动存档

AbilityTask 现在带有 `AutoSavegame` 标记。任务状态会在存档时保存，读档时恢复。计时器状态通过 `LoadDeferred` 机制恢复，不需要手动处理。

这意味着如果一个能力在执行过程中创建了 `WaitDelay` 任务并存档，读档后该任务会继续倒计时并在完成时触发回调。但前提是回调本身是可存档的（使用 `BindScriptFunction`）。如果回调用的是 `BindStdFunction`，读档后任务恢复但回调丢失，任务完成时不会触发任何逻辑。

### 16.5 选择指南

| 场景 | 推荐方式 | 原因 |
|---|---|---|
| 即时战斗逻辑，不涉及存档 | `BindStdFunction` | 简单直接，无需注册 |
| 持久化能力的回调 | `BindScriptFunction` | 读档后需要恢复 |
| ASC 事件监听（需要跨存档） | `AddScriptFunction` | multicast 委托的可存档绑定 |
| ASC 事件监听（临时） | `AddStdFunction` | 不需要跨存档 |
| AbilityTask 回调（需跨存档） | `BindScriptFunction` | 任务自动存档，回调也需可存档 |
| AbilityTask 回调（不跨存档） | `BindStdFunction` | 任务存档后回调丢失，任务完成时无副作用 |

---

## 17. 嵌套结构体 INI 加载

当一个 `IniComponent` 类的属性本身也是 `IniComponent` 结构体（非指针、无 Parser）时，INI 加载支持两种配置方式。加载时先尝试方式1，若未读到数据再尝试方式2。

### 17.1 适用条件

同时满足以下条件的属性支持两种加载方式：

- 属性类型**不是指针**（如 `FInheritedTagContainer`，而非 `GameplayEffect*`）
- 属性类型**没有 Parser 特化**（如 `GameplayTagRequirements`、`FInheritedTagContainer`）
- 属性所在类和属性类型都有 `CLASS(IniComponent)` 标签

有 Parser 的类型（如 `GameplayTagContainer`、`FScalableFloat`）和指针类型只走 Parser 路径，从 INI 读取单个字符串值。

### 17.2 方式1：点分键展开

在当前 section 下，用 `属性名.子字段名` 作为 INI key。支持多层嵌套（如 `A.B.C`）。

```ini
[Comp_BlockAbility]
$Type = BlockAbilityTagsGEComponent
InheritableBlockedAbilityTagsContainer.Added = Ability.Attack, Ability.Special
InheritableBlockedAbilityTagsContainer.Removed = Ability.Safe
```

### 17.3 方式2：section 引用

将属性值设为一个 section 名，然后去该 section 下用子字段名（无前缀）作为 key 读取。

```ini
[Comp_BlockAbility]
$Type = BlockAbilityTagsGEComponent
InheritableBlockedAbilityTagsContainer = MyBlockedTags

[MyBlockedTags]
Added = Ability.Attack, Ability.Special
Removed = Ability.Safe
```

### 17.4 涉及的嵌套结构体

| 结构体 | 使用场景 | 子字段 |
|--------|---------|--------|
| `FInheritedTagContainer` | `BlockAbilityTagsGEComponent.InheritableBlockedAbilityTagsContainer` | `Added`、`Removed`、`CombinedTags` |
| `GameplayTagRequirements` | `TagRequirementsGEComponent.Application/Ongoing/RemovalTagRequirements` | `RequireTags`、`IgnoreTags`、`TagQuery` |

### 17.5 执行顺序

加载时**先尝试方式1**（点分键），如果当前 section 下没有任何 `属性名.*` 的键被读到，**再尝试方式2**（section 引用）。两种方式不会互相干扰，但不能混用——如果方式1已经成功读到了数据，方式2不会执行。
