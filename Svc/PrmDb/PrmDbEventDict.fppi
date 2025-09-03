@ Parameter ID not found in database.
event PrmIdNotFound(
                        Id: FwPrmIdType @< The parameter ID
                    ) \
    severity warning low \
    id 0 \
    format "Parameter ID 0x{x} not found" \
    throttle 5

@ Parameter ID updated in database
event PrmIdUpdated(
                    Id: FwPrmIdType @< The parameter ID
                    ) \
    severity activity high \
    id 1 \
    format "Parameter ID 0x{x} updated"

@ Parameter database is full
event PrmDbFull(
                    Id: FwPrmIdType @< The parameter ID
                ) \
    severity fatal \
    id 2 \
    format "Parameter DB full when adding ID 0x{x} "


@ Parameter ID added to database
event PrmIdAdded(
                    Id: FwPrmIdType @< The parameter ID
                ) \
    severity activity high \
    id 3 \
    format "Parameter ID 0x{x} added"

@ Failed to write parameter file
event PrmFileWriteError(
                            stage: PrmWriteError @< The write stage
                            $record: I32 @< The record that had the failure
                            error: I32 @< The error code
                        ) \
    severity warning high \
    id 4 \
    format "Parameter write failed in stage {} with record {} and error {}"

@ Save of parameter file completed
event PrmFileSaveComplete(
                            records: U32 @< The number of records saved
                            ) \
    severity activity high \
    id 5 \
    format "Parameter file save completed. Wrote {} records."

@ Failed to read parameter file
event PrmFileReadError(
                        stage: PrmReadError @< The read stage
                        $record: I32 @< The record that had the failure
                        error: I32 @< The error code
                        ) \
    severity warning high \
    id 6 \
    format "Parameter file read failed in stage {} with record {} and error {}"

@ Load of parameter file completed
event PrmFileLoadComplete(
                            databaseString: string @< The database string
                            recordsTotal: U32 @< The number of records total
                            recordsAdded: U32 @< The number of new records added
                            recordsUpdated: U32 @< The number of records updated
                            ) \
    severity activity high \
    id 7 \
    format "Parameter file load completed. Database: {}, Records: {} ({} added and {} updated)."


event PrmSetFileComplete(
    records: U32 @< The number of records loaded
    ) \
    severity activity high \
    id 8 \
    format "Parameter set file completed. Applied {} records."