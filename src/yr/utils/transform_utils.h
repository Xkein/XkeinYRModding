#pragma once

class Transform;

class AbstractClass;

bool GetTransformFromYr(AbstractClass* yrObject, Transform& transform);

bool ApplyTransformToYr(AbstractClass* yrObject, const Transform& transform);

