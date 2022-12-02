DAYS = [
    "01",
    "02",
]

PARTS = [
    "1",
    "2",
]

[
    cc_binary(
        name = "main-{}-part{}".format(day, part),
        srcs = [
            "main.cpp",
            "solutions.h",
        ],
        defines = ["SOLUTION_{}_PART{}".format(day, part)],
        deps = [
            "//{}/part{}:Solution".format(day, part),
        ],
    )
    for day in DAYS
    for part in PARTS
]
