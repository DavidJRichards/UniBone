/* rk11.hpp: RK11 UNIBUS controller

 */
#ifndef _RK11_HPP_
#define _RK11_HPP_

#include <fstream>
#include <cstdint>

using namespace std;

#include "utils.hpp"
#include "unibusdevice.hpp"
#include "storagecontroller.hpp"
#include "rk05.hpp"

class rk11_c: public storagecontroller_c
{
private:

    // RK11 Registers (see Table 1-1 of manual):
    unibusdevice_register_t *RKDS_reg;  // Drive Status Register
    unibusdevice_register_t *RKER_reg;  // Error Register
    unibusdevice_register_t *RKCS_reg;  // Control Status Register
    unibusdevice_register_t *RKWC_reg;  // Word Count Register
    unibusdevice_register_t *RKBA_reg;  // Bus Address Register
    unibusdevice_register_t *RKDA_reg;  // Disk Address Register
    unibusdevice_register_t *RKDB_reg;  // Data Buffer Register

    // Drive Status Register (RKDS) bits (those not belonging to the RK05 drive itself)
    volatile uint16_t _id;   // On interrupt, contains the ID of the interrupting drive (3 bits).

    // Updates the RKDS DATI value based on the above bits
    void update_RKDS(void);

    // Error Register (RKER) bits
    bool _wce;          // Write Check error
    bool _cse;          // Checksum error
    bool _nxs;          // Nonexistent Sector error
    bool _nxc;          // Nonexistent Cylinder error
    bool _nxd;          // Nonexistent Drive error
    bool _te;           // Timing error
    bool _dlt;          // Data late error
    bool _nxm;          // Nonexistent memory error        
    bool _pge;          // Programming Error
    bool _ske;          // Seek error
    bool _wlo;          // Write Lockout Violation 
    bool _ovr;          // Overrun
    bool _dre;          // Drive Error

    // Updates the RKER DATI value based on the above bits
    void update_RKER(void);

    // Control/Status Register (RKCS) bits
    bool _go;		// Causes controller to execute function in _function when set
    uint16_t _function; // The function to perform (3 bits)
    uint16_t _mex;      // Extended address bits for transfer (2 bits)
    bool _ide;          // Interrupt on done when set
    bool _rdy;          // Whether the controller is ready to process a command	
    bool _sse;          // Whether to stop on a soft error
    bool _exb;		// Extra bit (unused, but diags expect it to be R/W)
    bool _fmt;          // Modifies read/write operations to allow formatting / header verification
    bool _iba;          // Inhibits incrementing RKBA
    bool _scp;          // Indicates that the last interrupt was due to a seek or reset function.
    bool _he;           // Indicates when a hard error has occurred.
    bool _err;          // Iindicates when any error has occurred 
 
    // Updates the RKCS DATI value based on above Status bits 
    void update_RKCS(void);

    // Disk Address Register (RKDA) bits
    volatile uint16_t _rkda_sector;
    volatile uint16_t _rkda_surface;
    volatile uint16_t _rkda_cyl;
    volatile uint16_t _rkda_drive;
 
    // Updates the RKDA DATI value based on the above bits.
    void update_RKDA(void);

    struct WorkerCommand
    {
        volatile rk05_c*  drive; 
        volatile uint32_t address;
        volatile uint16_t function;
        volatile bool     interrupt;
        volatile bool     stop_on_soft_error;
        volatile bool     format;
        volatile bool     iba;
    } _new_command;

    struct DMARequest
    {
        uint32_t address;
        uint16_t count;
        bool write;
        bool iba;
        uint16_t *buffer;
        bool timeout;
    };

    volatile bool _new_command_ready;   // Used in sync. between C/S register updates and worker thread.
                                   // If set, causes worker to abandon any current command and
                                   // pick up a new one.


    // Validates the given disk address, returns true if valid.
    // Sets the appropriate error flags if invalid (and returns false).
    bool validate_seek(void);

    // Increments RKDA to point to the next sector
    void increment_RKDA(void);

    // Causes an interrupt if IDE is set
    void invoke_interrupt(void);

    // Resets all register values on BUS INIT or Control Reset functions
    // and any other relevant local state.
    void reset_controller(void);

    rk05_c* selected_drive(void);
    
    bool check_drive_ready(void);

    bool check_drive_present(void);

    void dma_transfer(DMARequest &request);

    // Drive functions:
    enum Function
    {
       Control_Reset = 0,
       Write = 1,
       Read = 2,
       Write_Check = 3,
       Seek = 4,
       Read_Check = 5,
       Drive_Reset = 6,
       Write_Lock = 7,
    };

    enum WorkerState
    {
       Worker_Idle = 0,
       Worker_Execute = 1,
       Worker_Finish = 2,
    } _worker_state;

public:

    rk11_c();
    virtual ~rk11_c();    

    // background worker function
    void worker(void) override;

    // called by unibusadapter on emulated register access
    void on_after_register_access(
        unibusdevice_register_t *device_reg,
        uint8_t unibus_control) override;

    void on_power_changed(void) override;
    void on_init_changed(void) override;
  
    void on_drive_status_changed(storagedrive_c* drive);
};

#endif
