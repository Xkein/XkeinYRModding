#pragma once

class HelldiverComponent;
struct HelldiverStratagem;
class HelldiverStratagemInst;

class Helldivers
{
public:
    static void QueryStratagem(HelldiverComponent* com);
    static void ReturnStratagem(HelldiverStratagemInst* inst);

    static void Tick();

    static void Init();
    static void Clear();
};
