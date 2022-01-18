FROM scratch
ENTRYPOINT ["/dfiler"]
COPY dfiler /

VOLUME ["/source"]
VOLUME ["/target"]

WORKDIR /source
