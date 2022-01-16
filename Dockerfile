FROM scratch
ENTRYPOINT ["/dfiler"]
COPY dfiler LICENSE /

VOLUME ["/source"]
VOLUME ["/target"]
