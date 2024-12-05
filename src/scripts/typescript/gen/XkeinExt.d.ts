/// <reference path = "../index.d.ts"/>
declare module "XkeinExt" {
import { CDTimerClass } from "YRpp";
class PhysicsCollisionAddAndPersistResult
{
    m_com1 : PhysicsComponent;
    m_com2 : PhysicsComponent;
    m_point : any;
    m_normal : any;
}
class PhysicsCollisionRemoveResult
{
    m_com1 : PhysicsComponent;
    m_com2 : PhysicsComponent;
}
class PhysicsComponent
{
    m_owner : AbstractClass;
    m_type : PhysicsTypeComponent;
}
class PhysicsTypeComponent
{
    m_enable : boolean;
    m_isKinematic : boolean;
    m_isSensor : boolean;
    m_shapeType : EPhysicShapeType;
    m_mass : number;
    m_radius : number;
    m_halfHeight : number;
    m_halfExtent : any;
}
class ScriptComponent
{
    m_OnDtor : any;
    m_OnBeginUpdate : any;
    m_OnEndUpdate : any;
    m_OnSave : any;
    m_OnLoad : any;
    m_OnReceiveDamage : any;
    m_OnFire : any;
    m_OnDetonate : any;
    m_OnLaunch : any;
    m_OnCollisionEnter : any;
    m_OnCollisionPersist : any;
    m_OnCollisionExit : any;
}
}
