      SUBROUTINEPCSROB(N,IBLKN,IBLKS,IBTRM,IJAB,ND2I,NBLCKB,
     *NBLACK,P,IP,IJABP,IBTRMC,CP)
      IMPLICITDOUBLEPRECISION(A-H,O-Z)
      INTEGERN,IBLKN,IBLKS(*),IBTRM(*),NBLCKB,IJAB(*),ND2I,
     *P(*),IP(*),CP(*),NBLACK,IJABP(*),IBTRMC(*)
      LOGICALLOWER,UPPER,FULL,HALF,SYMMAT
      COMMON/PCVERL/LOWER,UPPER,FULL,HALF,SYMMAT
      SAVE/PCVERL/
      INTEGERI,L,J
      IF(HALF)THEN
      CALLPCSRIZ(IBLKN,IJAB,IJABP)
      CALLPCSRIX(IBLKN,IJAB,IJABP)
      ENDIF
      CALLPCSRO2(IBLKN,IJAB,IJABP,NBLCKB,P,IP)
      NBLACK=0
      ND2I=0
      IBTRMC(1)=1
      DO1L=1,NBLCKB
      IBTRMC(L+1)=IBTRMC(L)+IBLKS(P(L))
      NBLACK=NBLACK+IBLKS(P(L))
1     CONTINUE
      DO3L=NBLCKB+1,IBLKN
      IBTRMC(L+1)=IBTRMC(L)+IBLKS(P(L))
      ND2I=ND2I+IBLKS(P(L))*IBLKS(P(L))
3     CONTINUE
      I=0
      DO5L=1,NBLCKB
      DO7J=IBTRM(P(L)),IBTRM(P(L)+1)-1
      I=I+1
      CP(I)=J
7     CONTINUE
5     CONTINUE
      RETURN
      END