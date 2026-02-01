
declare module "YRpp" {
    class VectorClass<T> {
        constructor();
        constructor(capacity: number);
        SetCapacity(capacity: number): boolean;
        Clear(): void;
        FindItemIndex(item: T): number;
        GetItemIndex(item: T): number;
        GetItem(Index: number): T;
        Reserve(Index: number): boolean;
        Swap(other: VectorClass<T>): void;
        Capacity: number;
        IsInitialized: boolean;
        IsAllocated: boolean;
    }

    class DynamicVectorClass<T> extends VectorClass<T> {
        ValidIndex(index: number): boolean;
        AddItem(item: T): boolean;
        RemoveItem(index: number): boolean;
        Remove(item: T): boolean;
        AddUnique(item: T): boolean;
        Swap(other: DynamicVectorClass<T>): void;
        Count: number;
        CapacityIncrement: number;
    }

    class TypeList<T> extends DynamicVectorClass<T> {
        
    }

    class CounterClass extends VectorClass<number> {
        GetTotal(): number;
        EnsureItem(index: number): boolean;
        GetItemCount(index: number): number;
        Increment(index: number): number;
        Decrement(index: number): number;
        Total: number;
    }
}
