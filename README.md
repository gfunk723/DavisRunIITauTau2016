------------------
DavisRunIITauTau : Code For H->tau tau Run II analysis
------------------

For Quick Start (on SL6 only, CMSSW_7_6_3 and higher):


- Choose a location for your working directory :

		
		@ Fermilab LPC suggest : /uscms_data/d*/user_login_name  [* = 1,2,3,..]

		@ CERN Lxplus suggest : /afs/cern.ch/work/*/user_login_name  [* = 1st letter of user_login_name]

	
- Create a work area and clone the Davis code from Git (during installation you will be asked for a password):


		mkdir WORKING_DIR

		cd WORKING_DIR

		setenv GIT_ASKPASS

		voms-proxy-init -voms cms --valid=72:00

		source /cvmfs/cms.cern.ch/cmsset_default.csh

		setenv SCRAM_ARCH slc6_amd64_gcc530

		git clone git@github.com:gfunk723/DavisRunIITauTau2016 DavisRunIITauTau

		cd DavisRunIITauTau

		git checkout Moriond17_8_0_26patch1

		cd -

		./DavisRunIITauTau/install_everything.tcsh 


- Finally source the work env setup script (this step should be done each time you login from in CMSSW_7_4_14/src):

		source DavisRunIITauTau/setup_workEnv.*h [* = cs or b depending on your SHELL]


- Note : during the above installation you would have been asked for 2 passwords :

		[1] GRID password : https://twiki.cern.ch/twiki/bin/view/Main/CRABPrerequisitesGRIDCredentials

		[2] GitHub account & ssh key : http://cms-sw.github.io/faq.html 



