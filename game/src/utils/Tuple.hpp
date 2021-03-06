#ifndef TUPLE_H
#define TUPLE_H

template <typename T1, typename T2>
class Tuple {
	private:
		T1 fst;
		T2 snd;
	public:
		Tuple(T1 val1, T2 val2) : fst(val1), snd(val2) {}
		T1 getFst() { return fst; }
		T2 getSnd() { return snd; }
		void set(T1 val1, T2 val2) { fst = val1; snd = val2; }
};

template <typename T1, typename T2, typename T3>
class Triple {
	private:
		T1 fst;
		T2 snd;
		T3 thrd;
	public:
		Triple(T1 val1, T2 val2, T3 val3) : fst(val1), snd(val2), thrd(val3) {}
		T1 getFst() { return fst; }
		T2 getSnd() { return snd; }
		T3 getThrd() { return thrd; }
		void set(T1 val1, T2 val2, T3 val3) { fst = val1; snd = val2; thrd = val3; }
};

#endif
