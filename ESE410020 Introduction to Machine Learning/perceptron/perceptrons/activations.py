def get(fname):
    if fname == "sgn":
        return sgn

    raise AssertionError(f"Invalid activation function '{fname}'")


def sgn(value):
    # Sign function
    return 1 if value >= 0 else -1
