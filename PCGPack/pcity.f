      SUBROUTINEPCITY(PCIT,N,IJA,A,RHS,X,ISP,RSP,PRECON,
     *PCSTOP,PCMV)
      IMPLICITDOUBLEPRECISION(A-H,O-Z)
      INTEGERPCIT,N,IJA(*),ISP(*)
      DOUBLEPRECISIONA(*),RHS(*),X(*),RSP(*)
      EXTERNALPRECON,PCSTOP,PCMV
      INTEGERIERR,ITMAX,ITEST,KMAX,IFL,IPRE,PBLK,LUDONE,IBLK,
     *MNEED,ITS,RSDONE,NOVERF,RED1,RED2,IERR2,IFRMAT
      COMMON/PCCOM1/IERR,ITMAX,ITEST,KMAX,IFL,IPRE,PBLK,
     *LUDONE,IBLK,MNEED,ITS,RSDONE,NOVERF,RED1,RED2,IERR2,
     *IFRMAT
      SAVE/PCCOM1/
      INTEGERIPRE1,IPRE2,RATIO
      COMMON/PCCOM3/IPRE1,IPRE2,RATIO
      SAVE/PCCOM3/
      INTEGERNSP,RN,RP,P,AR,ATP,APAP,BIJ,NADR,NSP1
      NADR=ISP(2)
      NSP=ISP(1)
      RN=NADR+NSP-N
      IF(IPRE.EQ.1.OR.IPRE.EQ.3)THEN
      RP=RN
      ELSE
      RP=RN-N
      ENDIF
      P=RP-N*KMAX
      AR=P-N
      ATP=AR-N*KMAX
      APAP=ATP-MAX(1,KMAX)
      BIJ=APAP-MAX(1,KMAX)
      NSP1=BIJ-NADR
      ISP(3)=NSP1
      ISP(1)=NSP1
      IF(NSP1.LT.0)THEN
      RETURN
      ENDIF
      IF(IERR.NE.0)THEN
      RETURN
      ENDIF
      CALLPCITX(PCIT,N,IJA,A,RHS,X,RSP(RN),RSP(RP),RSP(P),RSP(AR),
     *RSP(ATP),RSP(APAP),RSP(BIJ),ISP,RSP,PRECON,PCSTOP,PCMV)
      RETURN
      END