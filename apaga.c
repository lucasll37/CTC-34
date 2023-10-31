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
