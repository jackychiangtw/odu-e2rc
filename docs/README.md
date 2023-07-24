# A. Directory Structure

```bash
l2
|__ build #contains files required to compile the code
|   |__ common #contains individual module's makefile
|   |__ config #contains main makefile to generate an 
|   |__ odu #contains scripts for logging, installing executable binary
|   |__ scripts #contains the configuration files netconf libraries and starting netopeer server
|   |__ yang #contains the YANG modules
|   |__ Makefile
|__ docs #contains README and other configuration files for building docs
|__ releases
|__ src #contains layer specific source code
|   |__ 5gnrmac : #MAC source code
|   |__ 5gnrrlc : #RLC source code
|   |__ cm : #common, environment and interface files
|   |__ cu_stub : #Stub code for CU
|   |__ du_app : #DU application and F1 code 
|   |__ mt : #wrapper functions over OS
|   |__ phy_stub : #Stub code for Physical layer
|   |__ rlog : #logging module
|   |__ O1 : #O1 module
|__ test
|__ tools
```

# B. Pre-requisite for Compilation

1. Linux 32-bit/64-bit machine
2. GCC version 4.6.3 and above
3. Install LKSCTP
   - On Ubuntu : 
        ```bash
        sudo apt-get install -y libsctp-dev
        ```
   - On CentOS : 
        ```bash
        sudo yum install -y lksctp-tools-devel
        ```
4. Install PCAP:
   - On ubuntu : 
        ```bash
        sudo apt-get install -y libpcap-dev
        ```
   - On CentOS : 
        ```bash
        sudo yum install -y libpcap-devel
        ```

# C. Pre-requisite for O1 Interface (Required only if run with O1 interface enabled) 

### 1. Setup netconf server

1. Add new netconf user (login with root user or use sudo and run following script)
    ```bash
    cd l2/build/scripts
    sudo ./add_netconf_user.sh
    ```

2. Install netconf packages.
    ```bash
    chmod +x install_lib_O1.sh
    sudo ./install_lib_O1.sh -c
    ```

### 2. Update the configuration according to your setup.
```bash
cd l2/build/config
```
1. Open the startup_config.xml and edit the desired IP and Port for CU, DU and RIC.
2. Open the nacm_config.xml and edit the desired user name to provide the access to that user.
3. Open the netconf_server_ipv6.xml and edit the desired netconf server configuration.
4. Open the oamVesConfig.json and edit the details of OAM VES collector.
5. Open the smoVesConfig.json and edit the details of SMO VES collector.
6. Open the netconfConfig.json and edit the details of Netopeer server.
   
### 3. Install the yang modules and load initial configuration:
```bash
cd l2/build/scripts
sudo ./load_yang.sh
```

### 4. Start Netopeer2-server:
```bash
cd l2/build/scripts
sudo ./netopeer-server.sh start
```
### 5. In case standard defined VES format is to be enabled (this step is optional): 
```bash
cd l2/src/o1/ves
```
Enable the Macro "StdDef" in file VesUtils.h
```bash
define StdDef
```  

# D. How to Clean and Build:
### 1. Build commands:
- ```odu```       - Builds all components of ODU
- ```cu_stub```   - Builds all CU Stub
- ```ric_stub```  - Builds all RIC_Stub
- ```clean_odu``` - clean up ODU
- ```clean_cu```  - clean up CU Stub
- ```clean_ric``` - clean up RIC Stub
- ```clean_all``` - cleanup everything

### **Options**:
- ```MACHINE=BIT64/BIT32``` - Specify underlying machine type. Default is BIT32
- ```NODE=TEST_STUB```      - Specify if it is a test node. Mandatory for cu_stub/ric_stub. Must not be used for odu
- ```MODE=FDD/TDD```        - Specify duplex mode. Default is FDD
- ```PHY=INTEL_L1```        - Specify type of phy. If not specified, PHY stub is used
- ```PHY_MODE=TIMER```      - Specify mode of phy. Used only if PHY=INTEL_L1. Default is radio mode
- ```O1_ENABLE=YES```       - Specify if O1 interface is enabled. If not specified, it is disabled 

### 2. Building ODU binary:
1. Build folder
    ```bash
    cd l2/build/odu
    ```
2. Building ODU binary
   
    Follow the [options](#options) commands in Section [D.1](#1-build-commands)
    ```bash
    make odu MACHINE=...  MODE=...
    ```
3. Cleaning ODU binary
   
    Follow the [options](#options) commands in Section [D.1](#1-build-commands)
    ```bash
    make clean_odu MACHINE=... MODE=...
    ```

### 3. Building CU Stub binary:
1. Build folder
    ```bash
    cd l2/build/odu
    ```
2. Building CU Stub binary
   
    Follow the [options](#options) commands in Section [D.1](#1-build-commands)
    ```bash
    make cu_stub NODE=... MACHINE=... MODE=...
    ```
3. Cleaning CU Stub binary
   
    Follow the [options](#options) commands in Section [D.1](#1-build-commands)
    ```bash
    make clean_cu NODE=... MACHINE=... MODE=...
    ```

### 4. Building RIC Stub binary:
1. Build folder
    ```bash
    cd l2/build/odu
    ```
2. Building RIC Stub binary
   
    Follow the [options](#options) commands in Section [D.1](#1-build-commands)
    ```bash
    make ric_stub NODE=... MACHINE=... MODE=...
    ```
3. Cleaning RIC Stub binary

    Follow the [options](#options) commands in Section [D.1](#1-build-commands)
    ```bash
    make clean_ric NODE=... MACHINE=... MODE=...
    ```

### 5. Cleaning ODU, CU Stub and RIC Stub:
```bash
make clean_all
```

# E. Clean and Build with O1 interface enabled (Requires pre-requisite steps in section [C](#c-pre-requisite-for-o1-interface-required-only-if-run-with-o1-interface-enabled))


### 1. Building ODU binary:
1. Build folder
    ```bash
    cd l2/build/odu
    ```
2. Build O-DU binary
   
    Follow the [options](#options) commands in Section [D.1](#1-build-commands)
    ```bash
    make odu MACHINE=... MODE=... O1_ENABLE=...
    ```
3. Clean O-DU binary
    
    Follow the [options](#options) commands in Section [D.1](#1-build-commands)
    ```bash
    make clean_odu MACHINE=... MODE=... O1_ENABLE=...
    ```

### 2. Building CU Stub binary:
1. Build folder
    ```bash
    cd l2/build/odu
    ```
2. Building CU Stub binary
        
    Follow the [options](#options) commands in Section [D.1](#1-build-commands)
    ```bash
    make cu_stub NODE=... MACHINE=... MODE=... O1_ENABLE=...
    ```
3. Cleaning CU Stub binary
        
    Follow the [options](#options) commands in Section [D.1](#1-build-commands)
    ```bash
    make clean_cu NODE=... MACHINE=... MODE=... O1_ENABLE=...
    ```

### 3. Building RIC Stub binary:
1. Build folder
    ```bash
    cd l2/build/odu
    ```
2. Building RIC Stub binary
        
    Follow the [options](#options) commands in Section [D.1](#1-build-commands)
    ```bash
    make ric_stub NODE=... MACHINE=... MODE=... O1_ENABLE=...
    ```
3. Cleaning RIC Stub binary
        
    Follow the [options](#options) commands in Section [D.1](#1-build-commands)
    ```bash
    make clean_ric NODE=... MACHINE=... MODE=... O1_ENABLE=...
    ```

### 4. Cleaning ODU, CU Stub and RIC Stub:
```bash
make clean_all
```

# F. How to execute:
### 1. Assign virtual IP addresses as follows:
1. ifconfig <interface name>:ODU "192.168.130.81"
2. ifconfig <interface name>:CU_STUB "192.168.130.82"
3. ifconfig <interface name>:RIC_STUB "192.168.130.80"

**PS**: If O1 interface is enabled, IP should match those configured in step [C.2.1](#2-update-the-configuration-according-to-your-setup).

### 2. Execute CU Stub:
```bash
cd l2/bin/cu_stub
./cu_stub
```

### 3. Execute RIC Stub:
```bash
cd l2/bin/ric_stub
./ric_stub
```

### 4. Execute DU:
```bash
cd l2/bin/odu
./odu
```

**PS**:
- CU stub and RIC stub must be run (in no particular sequence) before ODU
- In case O1 is enabled and SMO is not available run section [H](#h-push-cell-and-slice-configuration-over-o1-using-netopeer-cli) to start the stack.

# G. How to test with Intel L1:

## I. Compilation
### 1. Build ODU :
1. Create folder ```l2/src/wls_lib```. Copy ```wls_lib.h``` from <intel_directory>/phy/wls_lib/ to ```l2/src/wls_lib```.
1. Create folder ```l2/src/dpdk_lib```. Copy the following files from l2/src/dpdk_lib.
    ```bash
    intel
    |__ dpdk-19.11
        |__ x86_64-native-linuxapp-gcc
            |__ include
                |__ rte_branch_prediction.h
                |__ rte_common.h
                |__ rte_config.h
                |__ rte_dev.h
                |__ rte_log.h
                |__ rte_pci_dev_feature_defs.h
                |__ rte_bus.h
                |__ rte_compat.h
                |__ rte_debug.h
                |__ rte_eal.h
                |__ rte_os.h
                |__ rte_per_lcore.h
    ```
            
2. Build folder
    ```bash
    cd l2/build/odu
    ```
3. Build ODU Binary:

Follow the [options](#options) commands in Section [D.1](#1-build-commands).
```bash
make odu PHY=... PHY_MODE=... MACHINE=... MODE=...
```

### 2. Build CU Stub and RIC Stub:
Execute steps in sections [D.3](#3-building-cu-stub-binary) and [D.4](#4-building-ric-stub-binary)

## II. Execution
1. Click [here](https://docs.o-ran-sc.org/projects/o-ran-sc-o-du-phy/en/latest/) for assumptions, dependencies, pre-requisites etc for ODU-Low execution

2. Execute L1:
    1. Setup environment:
        ```bash
        cd <intel_directory>/phy/
        source ./setupenv.sh
        ```
    2. Run L1 binary :
        ```bash
        cd <intel_directory>/FlexRAN/l1/bin/nr5g/gnb/l1
        ```

        Option to run:
		1. In timer mode : 
            ```bash
            ./l1.sh -e
            ```
        2. In radio mode : 
            ```bash
            ./l1.sh -xran
            ```

        L1 is up when console prints follow:
        ```dos
        Non BBU threads in application
        ===========================================================================================================
        nr5g_gnb_phy2mac_api_proc_stats_thread: [PID:   8659] binding on [CPU  0] [PRIO:  0] [POLICY:  1]
        wls_rx_handler (non-rt):                [PID:   8663] binding on [CPU  0]
        ===========================================================================================================
                 
        PHY>welcome to application console
        ```
    3. Execute FAPI Translator:
        1. Setup environment:
            ```bash
            cd <intel_directory>/phy/
            source ./setupenv.sh
            ```
        2. Run FAPI translator binary:
            ```bash
            cd <intel_directory>/phy/fapi_5g/bin/
            ./oran_5g_fapi --cfg=oran_5g_fapi.cfg
            ```

    4. Execute CU Stub and RIC Stub:
        Run steps in sections [E.1](#1-building-odu-binary) - [E.3](#3-building-ric-stub-binary)

    5. Execute DU:
        1. DU execution folder
            ```bash
            cd l2/bin/odu
            export LD_LIBRARY_PATH=<intel_directory>/phy/wls_lib/lib:$LD_LIBRARY_PATH
            ./odu
            ```

# H. Push cell and slice configuration over O1 using netopeer-cli
When O-DU High is run with O1 enabled, it is waiting for initial cell configuration to be pushed by SMO before starting the stack. In case the SMO is not available then these configurations can be pushed via netopeer-cli as follows:

```bash
cd l2/build/config
netopeer2-cli
 > connect --login netconf
 Interactive SSH Authentication
 Type your password:
 Password: netconf!
 > edit-config --target candidate --config=cellConfig.xml
 > OK
 > commit
 > OK
 > edit-config --target candidate --config=rrmPolicy.xml
 > OK
 > commit
 > OK
```

For pushing these configurations in subsequent runs please edit cellConfig.xml and rrmPolicy.xml and increment number in the <id> tag to a new value e.g.

```bash
<id>rrm-2</id 
```


# I. How to execute the Health Check using netopeer-cli : get alarm-list
    
In case the SMO is not available the alarm list can be checked using netopeer-cli as follows:

```bash
netopeer2-cli
> connect --login netconf
Interactive SSH Authentication
Type your password:
Password: netconf!
> get --filter-xpath /o-ran-sc-odu-alarm-v1:odu/alarms
DATA
<odu xmlns="urn:o-ran:odu:alarm:1.0">
  <alarms>
    <alarm>
      <alarm-id>1009</alarm-id>
      <alarm-text>cell id  [1] is up</alarm-text>
      <severity>2</severity>
      <status>Active</status>
      <additional-info>cell UP</additional-info>
    </alarm>
  </alarms>
</odu>
```
The XML output is a list of active alarms in the O-DU High system.


# J. Troubleshooting Netconf server issues
In case the Netconf server and sysrepo breaks down, run the following steps:
```bash
cd l2/build/scripts
sudo ./troubleshoot_netconf.sh cleanup
```
execute section [C.3](#3-install-the-yang-modules-and-load-initial-configuration) and [C.4](#4-start-netopeer2-server) again
