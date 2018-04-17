
#include "ScriptMgr.h"
#include "InstanceScript.h"
#include "karazhan.h"




class spell_karazhan_brittle_bones : public SpellScriptLoader
{
public:
    spell_karazhan_brittle_bones() : SpellScriptLoader("spell_karazhan_brittle_bones") { }

    class spell_karazhan_brittle_bones_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_karazhan_brittle_bones_AuraScript);

        void CalcPeriodic(AuraEffect const* /*effect*/, bool& isPeriodic, int32& amplitude)
        {
            isPeriodic = true;
            amplitude = 5000;
        }

        void Update(AuraEffect const* effect)
        {
            PreventDefaultAction();
            if (roll_chance_i(35))
                GetUnitOwner()->CastSpell(GetUnitOwner(), SPELL_RATTLED, true);
        }

        void Register()
        {
            DoEffectCalcPeriodic += AuraEffectCalcPeriodicFn(spell_karazhan_brittle_bones_AuraScript::CalcPeriodic, EFFECT_0, SPELL_AURA_DUMMY);
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_karazhan_brittle_bones_AuraScript::Update, EFFECT_0, SPELL_AURA_DUMMY);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_karazhan_brittle_bones_AuraScript();
    }
};

class spell_karazhan_overload : public SpellScriptLoader
{
public:
    spell_karazhan_overload() : SpellScriptLoader("spell_karazhan_overload") { }

    class spell_karazhan_overload_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_karazhan_overload_AuraScript);

        void PeriodicTick(AuraEffect const* auraEffect)
        {
            PreventDefaultAction();
            GetUnitOwner()->CastCustomSpell(SPELL_OVERLOAD, SPELLVALUE_BASE_POINT0, int32(auraEffect->GetAmount() * (2.0, auraEffect->GetTickNumber())), GetUnitOwner(), true);
        }

        void Register()
        {
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_karazhan_overload_AuraScript::PeriodicTick, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
        }
    };

    AuraScript* GetAuraScript() const
    {
        return new spell_karazhan_overload_AuraScript();
    }
};

class spell_karazhan_blink : public SpellScriptLoader
{
public:
    spell_karazhan_blink() : SpellScriptLoader("spell_karazhan_blink") { }

    class spell_karazhan_blink_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_karazhan_blink_SpellScript);

        void HandleDummy(SpellEffIndex effIndex)
        {
            PreventHitDefaultEffect(effIndex);
            GetCaster()->getThreatManager().resetAllAggro();
            if (Unit* target = GetHitUnit())
                GetCaster()->CastSpell(target, SPELL_BLINK, true);
        }

        void Register()
        {
            OnEffectHitTarget += SpellEffectFn(spell_karazhan_blink_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
        }
    };

    SpellScript* GetSpellScript() const
    {
        return new spell_karazhan_blink_SpellScript();
    }
};


void AddSC_instance_karazhan()
{
    new instance_karazhan();
    new spell_karazhan_brittle_bones();
    new spell_karazhan_overload();
    new spell_karazhan_blink();
}
