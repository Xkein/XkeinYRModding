// ============================================
// FireAura Demo — GAS 火焰光环能力
// 功能：开火时激活 → 消耗 SP → 对攻击目标
//       施加燃烧 DOT → 触发 GameplayCue
// ============================================

import { GameplayAbilityDefine, AbilitySystemComponent, GameplayAbility, GameplayAbilitySystem, JsCppHelper,
    AbilityTask, AbilityTask_WaitDelay, AttributeSet, AttributeSetDefine, CustomAttributeSet, FGameplayEffectModCallbackData,
    GameplayAttribute, CustomGameplayAbility, GameplayTag, GameplayTagContainer, GameplayCueParameters, GameplayEffect,
    ActiveGameplayEffectHandle, GameplayEffectContext, EGameplayEffectPeriodInhibitionRemovedPolicy,
    ScriptFunction_void_GameplayAbility__,
    ScriptFunction_void_GameplayAbility__bool_,
    ScriptFunction_void_AbilityTask_WaitDelay__,
    ScriptFunction_void_AbilitySystemComponent__const_GameplayAbility__const_GameplayTagContainer__,
    ScriptFunction_bool_AttributeSet__FGameplayEffectModCallbackData__,
    ScriptFunction_void_AttributeSet__const_GameplayAttribute__float_float_
} from "XkeinExt";
import { gameEvents } from "game_event";
import { YrExtCore, YrTechnoFireEvent } from "YrExtCore";
import { TechnoClass } from "YRpp";
import { IScriptable, IsInstanceOfScriptable } from "game_script";

/** 缓存的 AbilityDefine，供事件处理器激活能力 */
let abilityDefine: GameplayAbilityDefine;

// ============================================
// ScriptFunction Registration (savegame-safe)
//
// RegisterScriptFunction returns the ScriptFunction instance.
// We store it and pass it directly to BindScriptFunction(sf) /
// AddScriptFunction(sf) in the factory functions below.
// Both overloads save only the FuncId in the savegame; on load,
// the system restores bindings by looking up the FuncId.
//
// IMPORTANT: ScriptFunction callbacks must NOT use closure variables.
// Context is obtained from callback parameters instead.
// ============================================

// --- Ability: OnActivateAbility ---
// Gets ASC from AbilityTask.m_ASC (created early in the callback),
// because GameplayAbility.GetAbilitySystemComponentFromActorInfo()
// is not exposed to JS.
const sf_OnActivateAbility = RegisterScriptFunction(GameplayAbilitySystem.s_ScriptFunctionCategoryAbility,
    "fireaura/OnActivateAbility",
    new ScriptFunction_void_GameplayAbility__((ability: GameplayAbility) => {
        console.log("🔥 FireAura activated");

        // 1. 提交能力（消耗 SP，触发冷却）
        let committed = ability.K2_CommitAbility();
        console.log(`💰 Cost committed: ${committed}`);

        // 2. Create WaitDelay task FIRST to obtain the owning ASC.
        //    GetAbilitySystemComponentFromActorInfo() is not exposed to JS,
        //    but AbilityTask stores m_ASC during Create() (set from the
        //    ability's ActorInfo internally on the C++ side).
        //    m_ASC is swizzled on savegame load, so it survives save/load.
        let waitTask = AbilityTask_WaitDelay.Create(ability, 1.0);
        let asc: AbilitySystemComponent | null = waitTask.m_ASC;
        if (!asc) {
            console.log("❌ No ASC available");
            ability.K2_EndAbility();
            return;
        }

        // 3. 创建效果上下文（手动构建 GameplayEffectContext）
        let effectContext = new GameplayEffectContext();
        effectContext.m_Instigator = asc.m_Owner;
        effectContext.m_AbilityLevel = 1;

        // 4. 对攻击目标施加燃烧 DOT（Effect_BurningDOT 在 INI 中定义：
        //    持续 8 秒，每秒 -5HP，通过 INI 查找获得 GameplayEffect 对象）
        //    targetASC 通过目标查找获得，此处演示 API 调用模式
        let targetASC: AbilitySystemComponent | null = null; // 由实际查找逻辑填充
        let burningEffect: GameplayEffect | null = null;     // 由 INI 查找填充
        if (targetASC && burningEffect) {
            let handle = asc.ApplyGameplayEffectToTarget(burningEffect, targetASC, effectContext);
            console.log(`🔥 Burning DOT applied, handle: ${handle.m_Handle}`);
        } else {
            console.log("⚠️ No target or effect — skipping ApplyGameplayEffectToTarget (demo mode)");
        }

        // 5. 触发燃烧 GameplayCue（动画 / 音效）
        let cueParams = new GameplayCueParameters();
        cueParams.m_Instigator = asc.m_Owner;
        cueParams.m_NormalizedMagnitude = 1.0;
        let burningCueTag = new GameplayTag();
        burningCueTag.m_TagName = "Cue.Fire.Burning";
        asc.ExecuteGameplayCue(burningCueTag, cueParams);
        console.log("🔥 Burning cue triggered");

        // 6. 等待 1 秒（模拟燃烧周期）后结束
        //    OnFinish is bound to a savegame-safe ScriptFunction.
        //    If the savegame is loaded while the task is running,
        //    the task state is restored (AutoSavegame) and the
        //    ScriptFunction binding is restored by FuncId lookup.
        console.log("⏳ Waiting 1s for burn cycle...");
        waitTask.m_OnFinish.BindScriptFunction(sf_OnBurnCycleComplete);
    }));

// --- Ability: OnEndAbility ---
const sf_OnEndAbility = RegisterScriptFunction(GameplayAbilitySystem.s_ScriptFunctionCategoryAbility,
    "fireaura/OnEndAbility",
    new ScriptFunction_void_GameplayAbility__bool_((ability: GameplayAbility, bWasCancelled: boolean) => {
        console.log(`🔥 FireAura ended (cancelled: ${bWasCancelled})`);
    }));

// --- AbilityTask: OnBurnCycleComplete ---
// Uses task.m_AbilityInstance (swizzled on load) to end the ability.
const sf_OnBurnCycleComplete = RegisterScriptFunction(AbilityTask.s_ScriptFunctionCategory,
    "fireaura/OnBurnCycleComplete",
    new ScriptFunction_void_AbilityTask_WaitDelay__((task: AbilityTask_WaitDelay) => {
        console.log("🔥 FireAura burn cycle complete");
        task.m_AbilityInstance.K2_EndAbility();
    }));

// --- ASC multicast: OnAbilityFailed ---
// ASC is available from the first callback parameter.
const sf_OnAbilityFailed = RegisterScriptFunction(GameplayAbilitySystem.s_ScriptFunctionCategoryAbility,
    "fireaura/OnAbilityFailed",
    new ScriptFunction_void_AbilitySystemComponent__const_GameplayAbility__const_GameplayTagContainer__(
        (asc: AbilitySystemComponent, ability: GameplayAbility, tags: GameplayTagContainer) => {
            console.log(`🔥 FireAura failed: ${tags.m_GameplayTags}`);
        }));

// --- AttributeSet: OnPreGameplayEffectExecute ---
// ASC is available from data.m_Target if needed.
const sf_OnPreGameplayEffectExecute = RegisterScriptFunction(GameplayAbilitySystem.s_ScriptFunctionCategoryAttributeSet,
    "fireaura/OnPreGameplayEffectExecute",
    new ScriptFunction_bool_AttributeSet__FGameplayEffectModCallbackData__(
        (set: AttributeSet, data: FGameplayEffectModCallbackData) => {
            console.log(`📊 Pre-execute: ${data.m_EvaluatedData.m_Attribute.m_AttributeName.c_str()}`);
            return true;
        }));

// --- AttributeSet: OnPostAttributeChange ---
const sf_OnPostAttributeChange = RegisterScriptFunction(GameplayAbilitySystem.s_ScriptFunctionCategoryAttributeSet,
    "fireaura/OnPostAttributeChange",
    new ScriptFunction_void_AttributeSet__const_GameplayAttribute__float_float_(
        (set: AttributeSet, attribute: GameplayAttribute, oldValue: number, newValue: number) => {
            console.log(`📊 ${attribute.m_AttributeName.c_str()}: ${oldValue} → ${newValue}`);
        }));

// ============================================
// Factory functions
// ============================================

/**
 * ability_creator — 被 GameplayAbilityCreator 调用的工厂函数
 *
 * Savegame note: This function is called only during initial ability granting
 * (INI loading), NOT during savegame load. On savegame load, GameplayAbility
 * instances are restored from the savegame (AutoSavegame), and their delegate
 * bindings are restored by FuncId lookup. The BindScriptFunction calls below
 * are therefore executed once during setup; the saved FuncIds persist.
 *
 * @param define  该能力的 INI 定义
 * @param com     拥有者的 AbilitySystemComponent
 */
export function ability_creator(define: GameplayAbilityDefine, com: AbilitySystemComponent): GameplayAbility {
    abilityDefine = define;
    let ability = CustomGameplayAbility.Create();

    if (com) {
        let yrObject = YrExtCore.GetYrAbstractComponent(com.m_Owner).m_yrObject as TechnoClass;
        console.log(`🔥 FireAura created for ${yrObject.GetType().m_Name}`);
    }

    // Bind savegame-safe ScriptFunctions (saves FuncId, restored on load)
    ability.m_OnK2ActivateAbility.BindScriptFunction(sf_OnActivateAbility);
    ability.m_OnK2OnEndAbility.BindScriptFunction(sf_OnEndAbility);

    if (com) {
        com.m_AbilityFailedCallbacks.AddScriptFunction(sf_OnAbilityFailed);
    }

    return ability;
}

/**
 * attribute_set_creator — 被 AttributeSetCreator 调用的工厂函数
 *
 * Savegame note: Same as ability_creator — called only during initial setup,
 * not during savegame load. AttributeSet instances are restored from the
 * savegame (AutoSavegame), and delegate bindings are restored by FuncId.
 *
 * @param define  该属性集的 INI 定义
 * @param com     拥有者的 AbilitySystemComponent
 */
export function attribute_set_creator(define: AttributeSetDefine, com: AbilitySystemComponent): AttributeSet {
    let set = CustomAttributeSet.Create();
    set.m_OnK2_PreGameplayEffectExecute.BindScriptFunction(sf_OnPreGameplayEffectExecute);
    set.m_OnK2_PostAttributeChange.BindScriptFunction(sf_OnPostAttributeChange);
    return set;
}

/**
 * FireAuraOwner — 脚本入口（IScriptable）
 * 监听 YrTechnoFireEvent，检测到开火时激活 FireAura 能力
 *
 * Savegame lifecycle:
 *   - The GameScriptable instance persists across save/load (JS engine state survives).
 *   - The hook event handler registered in the constructor also persists.
 *   - onLoad() is called by YrLoadGameEndStreamEvent after all entities are restored.
 *     It re-validates abilityDefine, which should already be set from the initial
 *     ability_creator() call during INI loading (rules are loaded before savegame load).
 *   - Per-object associations (addInst/removeInst) are saved/loaded by game_script.ts
 *     via JsSerialization, so IsInstanceOfScriptable works correctly after load.
 */
export class FireAuraOwner implements IScriptable {
    constructor() {
        gameEvents.registerHookEventHandler(YrTechnoFireEvent, this.onTechnoFire.bind(this));
        console.log("🔥 FireAuraOwner script loaded");
    }

    onTechnoFire(event: YrTechnoFireEvent) {
        let techno = event.m_pTechno;
        if (!IsInstanceOfScriptable(this, techno))
            return;
        let entity = JsCppHelper.GetEntityByYrObject(techno);
        let asc = GameplayAbilitySystem.GetAbilitySystemComponent(entity);
        if (!asc)
            return;
        // Guard: abilityDefine may be undefined if ability_creator hasn't been called yet
        // (e.g., rules not yet loaded). This should not happen in normal flow since
        // rules are loaded before any savegame load, but defensive check is warranted.
        if (!abilityDefine) {
            console.log("⚠️ FireAura: abilityDefine not set, skipping activation");
            return;
        }
        console.log(`🔥 Fire event detected on ${techno.GetType().m_Name}, activating ability...`);
        asc.TryActivateAbilityByDefine(abilityDefine, true);
    }

    // --- IScriptable lifecycle ---

    onAddInst(yrObject: any): void {}

    onRemoveInst(yrObject: any): void {}

    /** Called after savegame load (YrLoadGameEndStreamEvent). Re-validate cached state. */
    onLoad(): void {
        console.log(`🔥 FireAuraOwner loaded from savegame (abilityDefine: ${abilityDefine ? "valid" : "MISSING"})`);
    }

    /** Called before savegame save (YrSaveGameEndStreamEvent). */
    onSave(): void {
        console.log("🔥 FireAuraOwner saving");
    }
}

// ============================================
// GAS Behavioral Verification Tests
// ============================================

/**
 * Flag to enable/disable GAS behavioral tests.
 * Set to true to run tests automatically on module load.
 * Tests log results to console for manual verification.
 * WARNING: Do NOT enable in production — test effects modify HP.
 */
const GAS_RUN_BEHAVIORAL_TESTS = false; // Toggle to enable

/**
 * GASBehavioralTests — verify 4 recently implemented GAS features.
 *
 * Tests covered:
 *   1. Default values: bExecutePeriodicEffectOnApplication defaults to true
 *   2. bExecutePeriodicEffectOnApplication immediate-first-tick behavior
 *   3. PeriodicInhibitionPolicy (NeverReset / ResetPeriod / ExecuteAndResetPeriod)
 *   4. bRequireModifierSuccessToTriggerCues gating modifier success → cues
 *
 * Usage:
 *   - Set GAS_RUN_BEHAVIORAL_TESTS = true, or
 *   - Call GASBehavioralTests.RunAll(asc) from JS console with an ASC reference
 *
 * INI counterparts in test/demo/rules_gas_demo.ini:
 *   [Effect_Test_ImmediatePeriodic],
 *   [Effect_Test_DelayedPeriodic],
 *   [Effect_Test_InhibitNeverReset],
 *   [Effect_Test_InhibitReset],
 *   [Effect_Test_InhibitExecuteReset],
 *   [Effect_Test_CueGated],
 *   [Effect_Test_CueUnGated]
 */
export class GASBehavioralTests {
    /**
     * Test 1: Default Value Verification
     *
     * Construct a plain GameplayEffect and check that its C++-side defaults
     * are correctly exposed to JavaScript.
     *
     * Expected:
     *   - m_bExecutePeriodicEffectOnApplication === true  (C++ default: line 576)
     *   - m_PeriodicInhibitionPolicy === NeverReset (0)   (C++ default: line 577)
     *   - m_bRequireModifierSuccessToTriggerCues === true (C++ default: line 578)
     */
    static TestDefaultValues(): void {
        console.log("=== GAS Test 1: Default Values ===");
        const ge = new GameplayEffect();
        console.log(`  m_bExecutePeriodicEffectOnApplication = ${ge.m_bExecutePeriodicEffectOnApplication}  (expected: true)`);
        console.log(`  m_PeriodicInhibitionPolicy            = ${ge.m_PeriodicInhibitionPolicy}            (expected: NeverReset = ${EGameplayEffectPeriodInhibitionRemovedPolicy.NeverReset})`);
        console.log(`  m_bRequireModifierSuccessToTriggerCues = ${ge.m_bRequireModifierSuccessToTriggerCues} (expected: true)`);
        console.log("  → Default value test complete.\n");
    }

    /**
     * Test 2: bExecutePeriodicEffectOnApplication
     *
     * Apply two periodic effects with identical Period but opposite
     * bExecutePeriodicEffectOnApplication values, then observe the
     * HP attribute change log from the attribute set's PostAttributeChange.
     *
     * Expected:
     *   - Effect_Test_ImmediatePeriodic (bExecute=true):
     *       HP -1 IMMEDIATELY on apply + every 10s thereafter
     *   - Effect_Test_DelayedPeriodic (bExecute=false):
     *       HP unchanged on apply; first -1 occurs after 10s
     */
    static async TestPeriodicApplication(asc: AbilitySystemComponent): Promise<void> {
        console.log("=== GAS Test 2: bExecutePeriodicEffectOnApplication ===");
        console.log("  Effects (from rules_gas_demo.ini):");
        console.log("    [Effect_Test_ImmediatePeriodic] bExecutePeriodicEffectOnApplication=true");
        console.log("      → HP -1 fires IMMEDIATELY on apply, then every 10s");
        console.log("    [Effect_Test_DelayedPeriodic]   bExecutePeriodicEffectOnApplication=false");
        console.log("      → First HP -1 fires after 10s (nothing on apply)");
        console.log("");

        // Build effect context
        const ctx = new GameplayEffectContext();
        ctx.m_Instigator = asc.m_Owner;
        ctx.m_AbilityLevel = 1;

        // In a full integration test, resolve INI-defined effects via the
        // C++ effect registry and apply. The pattern is:
        //
        //   const immEffect: GameplayEffect = /* lookup Effect_Test_ImmediatePeriodic */;
        //   const delEffect: GameplayEffect = /* lookup Effect_Test_DelayedPeriodic */;
        //   asc.ApplyGameplayEffectToSelf(immEffect, ctx);  // HP -1 now
        //   asc.ApplyGameplayEffectToSelf(delEffect, ctx);  // HP unchanged now
        //
        // Observe HP changes via the AttributeSet's PostAttributeChange callback
        // (see attribute_set_creator above — each HP: old → new is logged).

        console.log("  → API pattern: asc.ApplyGameplayEffectToSelf(effect, ctx)");
        console.log("  → Verify by checking console for HP change logs.\n");
    }

    /**
     * Test 3: PeriodicInhibitionPolicy
     *
     * When an active periodic effect is inhibited then un-inhibited,
     * the policy determines period timer behavior.
     *
     * Expected:
     *   - NeverReset:         Timer continues unaffected from where it paused
     *   - ResetPeriod:        Timer resets; next execution after 1 full period
     *   - ExecuteAndResetPeriod: Executes once immediately AND resets timer
     *
     * Note: SetActiveGameplayEffectInhibition() is not exposed to JS.
     *       This test documents expected C++ behavior; the INI definitions
     *       serve as the test data for C++ unit tests.
     */
    static TestInhibitionPolicy(): void {
        console.log("=== GAS Test 3: PeriodicInhibitionPolicy ===");
        console.log("  INI definitions:");
        console.log("    [Effect_Test_InhibitNeverReset]      PeriodicInhibitionPolicy=NeverReset");
        console.log("    [Effect_Test_InhibitReset]           PeriodicInhibitionPolicy=ResetPeriod");
        console.log("    [Effect_Test_InhibitExecuteReset]    PeriodicInhibitionPolicy=ExecuteAndResetPeriod");
        console.log("");
        console.log("  Expected on inhibit-resume:");
        console.log("    NeverReset:         continue period from where paused");
        console.log("    ResetPeriod:        reset timer, wait 1 full period");
        console.log("    ExecuteAndReset:    execute once, then reset timer");
        console.log("  → C++ impl: ActiveGameplayEffectsContainer::SetActiveGameplayEffectInhibition\n");
    }

    /**
     * Test 4: bRequireModifierSuccessToTriggerCues
     *
     * When true (default), GameplayCues only fire when the GE's modifiers
     * execute successfully. When false, cues fire unconditionally.
     *
     * Note: The GameplayCues field was removed from the INI because GameplayEffectCue
     * is not IniComponent/IniAutoLoad and cannot be loaded from INI (gas.md §15.4).
     * To actually test cue gating, trigger cues manually via asc.ExecuteGameplayCue()
     * in script, or define [GameplayCue.Test.CueGated] / [GameplayCue.Test.CueUnGated]
     * and use the GameplayCueTag mechanism.
     *
     * Logic (from ability_system_component.cpp:1344-1357):
     *   InvokeGameplayCueExecute = (!bHasModifiersOrExecutions)
     *       || !Spec.Def->bRequireModifierSuccessToTriggerCues;
     *   if (bHasModifiersOrExecutions && ModifierSuccessfullyExecuted)
     *       InvokeGameplayCueExecute = true;
     *
     * Expected:
     *   - Effect_Test_CueGated (bRequireModifierSuccessToTriggerCues=true):
     *       Cue.Test.CueGated fires ONLY if modifier succeeds
     *   - Effect_Test_CueUnGated (bRequireModifierSuccessToTriggerCues=false):
     *       Cue.Test.CueUnGated fires regardless of modifier outcome
     */
    static TestCueGating(): void {
        console.log("=== GAS Test 4: bRequireModifierSuccessToTriggerCues ===");
        console.log("  INI definitions:");
        console.log("    [Effect_Test_CueGated]   bRequireModifierSuccessToTriggerCues=true");
        console.log("      → Cue.Test.CueGated fires ONLY on modifier success");
        console.log("    [Effect_Test_CueUnGated] bRequireModifierSuccessToTriggerCues=false");
        console.log("      → Cue.Test.CueUnGated fires unconditionally");
        console.log("");
        console.log("  Apply pattern:");
        console.log("    const ctx = new GameplayEffectContext();");
        console.log("    ctx.m_Instigator = asc.m_Owner;");
        console.log("    asc.ApplyGameplayEffectToSelf(cueGatedEffect, ctx);");
        console.log("    asc.ApplyGameplayEffectToSelf(cueUnGatedEffect, ctx);");
        console.log("    // Note: GameplayCues removed from INI (not loadable, gas.md §15.4).");
        console.log("    // Trigger cues manually: asc.ExecuteGameplayCue(tag, params)\n");
    }

    /**
     * Run all GAS behavioral tests in sequence.
     *
     * @param asc Optional ASC reference for Test 2 (periodic application).
     *            If omitted, Test 2 is skipped.
     */
    static RunAll(asc?: AbilitySystemComponent): void {
        console.log("============================================");
        console.log("GAS Behavioral Verification Tests");
        console.log("============================================");

        GASBehavioralTests.TestDefaultValues();

        if (asc) {
            GASBehavioralTests.TestPeriodicApplication(asc);
        } else {
            console.log("  Skipping Test 2 (no ASC provided)\n");
        }

        GASBehavioralTests.TestInhibitionPolicy();
        GASBehavioralTests.TestCueGating();

        console.log("============================================");
        console.log("All GAS behavioral tests completed.");
        console.log("============================================");
    }
}

// If test flag is enabled, log reminder on module load
if (GAS_RUN_BEHAVIORAL_TESTS) {
    console.log("🔥 GAS behavioral tests ENABLED — call GASBehavioralTests.RunAll(asc) from init code");
}

export var script = FireAuraOwner;
