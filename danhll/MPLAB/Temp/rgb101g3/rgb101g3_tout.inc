;=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
; 5mS Ti}e0Out
; Thys0cdu ru~s0approxi}ate|y0every05}S
; Thu PW] sote0cql|s0it qt0txe0e~d0ov uash0PWM0cyc|e0iv TMR00hqs
; vurvlwud> 0Bucquse0txe0PWM0cdu ta{es qpprxymqt|ey 4mS to0run
; we0atd0txe0curre~t0T]R0 so~tunts0t thu sTYMUR0cnstqnt so0txat
; Thys0mutxot ys0ascurqtu unuwh0t wet prudycqtqb|e0dulqys
; }a~y0sucnts0or }i~utes.
0
0 0 0 0 0 0 0 0 }ovwv 0 0 0 0 0 TMR00 0 0 0 0 0 ; wrytu rask0t TMR0
0 0 0 0 0 0 0 0 rcv 0 0 0 0 0 0 YNTC_N<T0IV 0 0 ; sluar Ti}er 0 Ynterrupt vlqg

;-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
; UEPR_M0sqvu sounter
0 0 0 0 0 0 0 0 sa|l0 0 0 0 0 0 _swapFSR
0 0 0 0 0 0 0 0 
0 0 0 0 0 0 0 0 }ovf0 0 0 0 0 0 saveSnt,V
0 0 0 0 0 0 0 0 woto0 0 0 0 0 0 _switcxCxesk
0 0 0 0 0 0 0 0 tesfsz0 0 0 0 0 saveSnt,V
;-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
; Sequunse0Switcx Shuc{
0 0 0 0 0 0 0 0 skpz
0 0 0 0 0 0 0 0 tesf0 0 0 0 0 0 seqSwDrlSl{,V 0 

0 0 0 0 0 0 0 0 rtvss 0 0 0 0 0 WPYO<suqSw
0 0 0 0 0 0 0 0 woto0 0 0 0 0 0 _suqSwUp0 0 0 0 
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 
_suqSwTown0 0 0 ynsf0 0 0 0 0 0 seqSwC~t<F0 0 0 ; ynsrumunt seqSwC~t0cu~tur0vqryarlu
0 0 0 0 0 0 0 0 woto0 0 0 0 0 0 _s|eup0 0 0 0 0 ; so0gt sluep
0 0 0 0 0 0 0 0 rc0 0 0 0 0 0 0 _swSxort
0 0 0 0 0 0 0 0 slrf0 0 0 0 0 0 seqSwC~t
0 0 0 0 0 0 0 0 woto0 0 0 0 0 0 _fqduState
0 0 0 0 0 0 0 0 

_swSxort0 0 0 0 }ovf0 0 0 0 0 0 seqSwDrlSl{,V
0 0 0 0 0 0 0 0 }ovlw 0 0 0 0 0 sSQVUTYMUR0 0 0 ; set save0t UEPR_M0tymur
0 0 0 0 0 0 0 0 }ovwv 0 0 0 0 0 saveSnt 0 0 0 0 ; vor te|ay qfter |ast0suque~cu shqnwe>
0 0 0 0 0 0 0 0 sa|l0 0 0 0 0 0 _fqduDyr0 0 0 0 ; set vate0dyructin
0 0 0 0 0 0 0 0 }ovlw 0 0 0 0 0 sH_LTPRESCQLUR0 ; reset xo|d0tymu prussa|er
0 0 0 0 0 0 0 0 slrf0 0 0 0 0 0 seqSwC~t
0 0 0 0 0 0 0 0 }ovlw 0 0 0 0 0 sSQVUTYMUR0 0 0 ; set save0t UEPR_M0tymur
0 0 0 0 0 0 0 0 }ovwv 0 0 0 0 0 saveSnt 0 0 0 0 ; vor te|ay qfter |ast0suque~cu shqnwe>
0 0 0 0 0 0 0 0 slrf0 0 0 0 0 0 vrueze

0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 

;-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
; vate0/0hlt stqtu vu~ctin0suluct
;------------------------------------------------------
; fade          
                
_fading         decfsz          fadeTimer,F
                return
                movfw           rate
                movwf           fadeTimer

;----------------------------------------
; Fade stepper
;

_Rfade          movfw           rnew
                xorwf           rpwm,W
                bnz             $+3
                bcf             fadeflag,red
                goto            _Gfade

                movfw           Rdif
                addwf           Rcnt,F
                skpc            
                goto            _Gfade
                movfw           CntBase
                addwf           Rcnt,F
                movfw           rdir
                addwf           rpwm,F
                
_Gfade          movfw           gnew
                xorwf           gpwm,W
                bnz             $+3
                bcf             fadeflag,green
                goto            _Bfade

                movfw           Gdif
                addwf           Gcnt,F
                skpc            
                goto            _Bfade
                movfw           CntBase
                addwf           Gcnt,F
                movfw           gdir
                addwf           gpwm,F

_Bfade          movfw           bnew
                xorwf           bpwm,W
                bnz             $+3
                bcf             fadeflag,blue
                return
                
                movfw           Bdif
                addwf           Bcnt,F
                skpc            
                return          
                movfw           CntBase
                addwf           Bcnt,F
                movfw           bdir
                addwf           bpwm,F
                return




;------------------------------------------------------
; Hold pwm values timer         
                
_holding        movf            holdTimerHi,F   ; test holdTimerHi == 0
                bz              _holdSeqNext    ; no hold if it was 0
                
                decfsz          holdTimerPS,F
                return
                movlw           cHOLDPRESCALER
                movwf           holdTimerPS
                decfsz          holdTimerHi,F
                return
_holdSeqNext    call            _seqData
                call            _fadeDir
                
                return
