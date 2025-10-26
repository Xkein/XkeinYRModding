
declare module "YRpp" {
    class VectorClass<T> {
        Clear(): void;
        GetItem(Index: number): T;
        Reserve(Index: number): boolean;
        Capacity: number;
    }

    class CounterClass extends VectorClass<number> {

    }
}
