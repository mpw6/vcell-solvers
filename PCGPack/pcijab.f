      SUBROUTINEPCIJAB(N,IJA,IBLKN,NZRBMX,IBLKS,IRTBM,IJAB,MARK)
      IMPLICITDOUBLEPRECISION(A-H,O-Z)
      INTEGERN,IJA(*),IBLKN,NZRBMX,IBLKS(*),IRTBM(*),IJAB(*),
     *MARK(*)
      INTEGERIERR,ITMAX,ITEST,KMAX,IFL,IPRE,PBLK,LUDONE,IBLK,
     *MNEED,ITS,RSDONE,NOVERF,RED1,RED2,IERR2,IFRMAT
      COMMON/PCCOM1/IERR,ITMAX,ITEST,KMAX,IFL,IPRE,PBLK,
     *LUDONE,IBLK,MNEED,ITS,RSDONE,NOVERF,RED1,RED2,IERR2,
     *IFRMAT
      SAVE/PCCOM1/
      INTEGERI,J,K,J1,J2,K1,K2,BJ,NZRB
      CALLPC0VI(IBLKN,MARK)
      NZRB=IBLKN+1
      IF(NZRB.GT.NZRBMX)THEN
      IERR=10
      NZRBMX=3*IBLKN+1
      RETURN
      ENDIF
      IJAB(1)=NZRB+1
      K2=0
      J2=IJA(1)-1
      DO1I=1,IBLKN
      MARK(I)=I
      K1=K2+1
      K2=K2+IBLKS(I)
      DO3K=K1,K2
      J1=J2+1
      J2=IJA(K+1)-1
CVDIR IGNORE RECRDEPS
CDIR$ IVDEP
      DO5J=J1,J2
      BJ=IRTBM(IJA(J))
      IF(MARK(BJ).NE.I)THEN
      NZRB=NZRB+1
      IF(NZRB.GT.NZRBMX)THEN
      IERR=10
      NZRBMX=(NZRB-IBLKN-1)*IBLKN/I+IBLKN+1
      RETURN
      ENDIF
      IJAB(NZRB)=BJ
      MARK(BJ)=I
      ENDIF
5     CONTINUE
3     CONTINUE
      IJAB(I+1)=NZRB+1
1     CONTINUE
      RETURN
      END
