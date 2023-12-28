#include "fsal/fatfs/DriverFatFs.hpp"
#include "hal/synchronous_interfaces/SynchronousDisk.hpp"
#include "infra/util/ByteRange.hpp"
#include "source/diskio.h"

namespace fsal
{
    void DriverFatFs::RegisterDriver(hal::SynchronousDisk& interface) const
    {
        drivers.emplace_back(interface);
    }

    void DriverFatFs::UnregisterDriver(const hal::SynchronousDisk& interface)
    {
        drivers.erase(std::find(drivers.begin(), drivers.end(), interface));
    }

    hal::SynchronousDisk& DriverFatFs::Interface(uint8_t index)
    {
        return drivers[index].interface;
    }
}

extern "C"
{
    DSTATUS disk_initialize(BYTE pdrv)
    {
        fsal::DriverFatFs::Instance().Interface(pdrv).Initialize();
        return 0;
    }

    DSTATUS disk_status(BYTE pdrv)
    {
        auto status = fsal::DriverFatFs::Instance().Interface(pdrv).Status();

        if (status == hal::SynchronousDisk::Status::notInitialized)
            return STA_NOINIT;
        if (status == hal::SynchronousDisk::Status::noDiskAvailable)
            return STA_NODISK;
        if (status == hal::SynchronousDisk::Status::writeProtected)
            return STA_PROTECT;

        return 0;
    }

    DRESULT disk_read(BYTE pdrv, BYTE* buff, LBA_t sector, UINT count)
    {
        fsal::DriverFatFs::Instance().Interface(pdrv).Read(infra::ByteRange(buff, buff + count), sector);
        return RES_OK;
    }

    DRESULT disk_write(BYTE pdrv, const BYTE* buff, LBA_t sector, UINT count)
    {
        fsal::DriverFatFs::Instance().Interface(pdrv).Write(infra::ConstByteRange(buff, buff + count), sector);
        return RES_OK;
    }

    DRESULT disk_ioctl(BYTE pdrv, BYTE cmd, void* buff)
    {
        if (cmd == CTRL_SYNC)
            fsal::DriverFatFs::Instance().Interface(pdrv).Sync();
        else if (cmd == GET_SECTOR_COUNT)
            *reinterpret_cast<DWORD*>(buff) = fsal::DriverFatFs::Instance().Interface(pdrv).MediaSize();
        else if (cmd == GET_SECTOR_SIZE)
            *reinterpret_cast<DWORD*>(buff) = fsal::DriverFatFs::Instance().Interface(pdrv).SectorSize();
        else if (cmd == GET_BLOCK_SIZE)
            *reinterpret_cast<DWORD*>(buff) = fsal::DriverFatFs::Instance().Interface(pdrv).BlockSize();
        else
            return RES_ERROR;

        return RES_OK;
    }
}