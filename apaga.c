program Create_Minimal_Transducer_for_Given_List(input, output);
var
    MinimalTransducerStatesDictionary: Dictionary;
    TempStates: array [0..MAX_WORD_SIZE] of STATE;
    InitialState: STATE;
    PreviousWord, CurrentWord, CurrentOutput,
        WordSuffix, CommonPrefix: string;
    tempString: string;
    tempSet: set of string;
    i, j, PrefixLengthPlus1: integer;
    c: char;
    function FindMinimized(s: STATE): STATE;
    {return an equivalent state from the dictionary.
        If not present inserts a copy of the parameter to the dictionary
        and returns it.}
    var r: STATE;
    begin
        r:= MEMBER(MinimalTransducerStatesDictionary, s);
        if r = NULL then begin
            r:= COPY_STATE(s);
            INSERT(r);
        end;
        return(r);
    end; {FindMinimized}
begin
    MinimalTransducerStatesDictionary := NEW_DICTIONARY;
    for i := 0 to MAX_WORD_SIZE do
        TempStates[i] := NEW_STATE;
    PreviousWord := '';
    CLEAR_STATE(TempState[0]);
    while not eof(input) do begin
    {Loop for the words in the input list}
        readln(input, CurrentWord, CurrentOutput);
        {the following loop calculates the length of the longest
        common prefix of CurrentWord and PreviousWord}

        i:=1;
        while (i < length(CurrentWord)) and (i < length(PreviousWord)) and
            (CurrentWord[i] = PreviousWord[i]) do
            i:= i+1;
        PrefixLengthPlus1 := i;
        {we minimize the states from the suffix of the previous word}
        for i:=length(PreviousWord) downto PrefixLengthPlus1 do
            SET_TRANSITION(TempStates[i-1], PreviousWord[i], FindMinimized(TempStates[i]));
                FindMinimized(TempStates[i]);
        {This loop initializes the tail states for the current word}
        for i:=PrefixLengthPlus1 to length(CurrentWord) do begin
            CLEAR_STATE(TempStates[i]);
            SET_TRANSITION(TempStates[i-1], CurrentWord[i], TempStates[i]);
        end;
        if CurrentOutput <> PreviousWord then begin
            SET_FINAL(TempStates[length(CurrentWord)], true);
            SET_OUTPUT(TempStates[length(CurrentWord)], {"});
        end;
        for j:=1 to PrefixLengthPlus1-1 do begin
            CommonPrefix := OUTPUT(TempStates[j-1], CurrentWord[j]); /\ CurrentWord[j];
            WordSuffix := CommonPrefix(^-1) OUTPUT(TempStates[j-1], CurrentWord[j]);
            SET_OUTPUT(TempStates[j-1], CurrentWord[j], CommonPrefix);
            for c:= FIRST_CHAR to LAST_CHAR do begin
                if TRANSITION(TempStates[j], c) <> NULL then
                    SET_OUTPUT(TempStates[j], c, concat(WordSuffix, OUTPUT(TempStates[j], c)));
            end;
            if FINAL(TempStates[j]) then begin
                tempSet:= Ø
                for tempString in STATE_OUTPUT(TempStates[j]) do
                    tempSet:= tempSet + concat(WordSuffix, tempString);
                SET_STATE_OUTPUT(TempStates[j], tempSet);
            end;
            CurrentOutput:=CommonPrefix(^-1) CurrentOutput;
        end;
        if CurrentWord = PreviousWord then
            SET_STATE_OUTPUT(TempStates[length(CurrentWord)],
                STATE_OUTPUT(TempStates[length(CurrentWord)]) + CurrentOutput);
        else SET_OUTPUT(TempStates[PrefixLengthPlus1-1],
                CurrentOutput[PrefixLengthPlus1], CurrentOutput);
        PreviousWord := CurrentWord;
    end; {while}
    {here we are minimizing the states of the last word}
    for i:= length(CurrentWord) downto 1 do
        SET_TRANSITION(TempStates[i-1], PreviousWord[i], FindMinimized(TempStates[i]));
    InitialState := FindMinimized(TempStates[0]);
    PRINT_TRANSDUCER(output, InitialState);
end; {Create_Minimal_Transducer_for_Given_List}
