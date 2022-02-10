#pragma once

#include <ydb/library/yql/providers/dq/task_runner/file_cache.h> 

#include <util/generic/list.h>

namespace NYql {

class TFileCache: public IFileCache {
public:
    explicit TFileCache(const TString& baseDir, i64 size);

    void AddFile(const TString& path, const TString& md5) override;

    TMaybe<TString> FindFile(const TString& md5) override;

    void Walk(const std::function<void(const TString& objectId)>&) override;

    ui64 FreeDiskSize() override;

    ui64 UsedDiskSize() override;

    bool Contains(const TString& objectId) override;

    TString GetDir() override {
        return BaseDir;
    };

private:
    TString GetDir(const TString& md5) const;

    void Scan();
    void Clean();

    TString BaseDir;

    struct TFileObject {
        TString ObjectId;
        TString Name;
        ui64 Size = 0;
        ui64 LastAccess = 0;
        TList<TString>::iterator Position;
    };
    TList<TString> LRU;
    THashMap<TString, TFileObject> Files;
    ui64 UsedSize = 0;
    ui64 TotalSize = 0;

    TMutex Mutex;
};

} // namespace NYql
